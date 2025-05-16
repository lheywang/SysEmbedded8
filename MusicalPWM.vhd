LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY MusicalPWM IS
    PORT (
        -- INPUTS
        control : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        -- Control is interpreted as the following :
        -- Bit 31 : Global Reset / EN of the PWM. Maintain to 1 to disable any operations
        -- Bit 30 : Start note. Shall be set to 0 then 1 to restart
        -- Bits 29-24 : Unused
        -- Bits 23-16 : Duration in pack of 10 ms : 1 = 10 ms, 10 = 10ms ... 255 = 2550 ms.
        -- Bits 15- 8 : Volume. 255 = MAX volume, 0 = mute.
        -- Bits 7 - 0 : Note.   1 = Do1, 
        --                      2 = Do1#, 
        --                      3 = Re1, 
        --                      4 = Re1#, 
        --                      5 = Mi1, 
        --                      6 = Fa1, 
        --                      7 = Fa1#, 
        --                      8 = Sol1, 
        --                      9 = Sol1#,
        --                      10= La1,
        --                      11= Si1b,
        --                      12= Si1,
        --                      13= Do2,
        --                      ...
        --                      96=Si7
        clk : IN STD_LOGIC;     -- 50 MHz clock

        -- OUTPUTS
        status : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)   := "00000000";
        -- Status expres the current state of some functions
        -- Bit 7 :  '1' : The sent note is invalid.
        -- Bit 6 :  '1' : The previous note has ended.
        -- Bit 5 :  Unused. Set to 0 by the hardware
        -- Bit 4 :  Unused. Set to 0 by the hardware
        -- Bit 3 :  '1' : Duration requested is 0. No tone will be outputed.
        -- Bit 2 :  '1' : Volume is 0 and is thus, muted. '0' otherwise.
        -- Bit 1 :  '1' : PWM is actually generated on the output, '0' otherwise.
        -- Bit 0 :  '1' : Restart needed for the next note, '0' otherwise (note can be launched at any time).
        pwm : OUT STD_LOGIC                         := '0'
    );
END ENTITY;

ARCHITECTURE behavioral OF MusicalPWM IS

    -- Signals --
    -- Configurations vectors
    SIGNAL maxv : STD_LOGIC_VECTOR(31 DOWNTO 0) := (OTHERS => '0');
    SIGNAL duty : STD_LOGIC_VECTOR(31 DOWNTO 0) := (OTHERS => '0');

    -- Counter signal
    SIGNAL act : INTEGER RANGE 0 TO 800_000     := 0;

    -- Duration counters
    SIGNAL duration_cnt : INTEGER RANGE 0 TO 600_000 := 0;
    SIGNAL duration : INTEGER RANGE 0 TO 255    := 0;
    SIGNAL run_enabled : STD_LOGIC              := '0';
    SIGNAL pwm_enabled : STD_LOGIC              := '0';

    -- Architecture --
BEGIN

    -- First, pass the inputs values to our LUT to cast the different types
    U1 : ENTITY work.MusicalPWM_freq(behavioral)
        PORT MAP(
            frequz => control(7 DOWNTO 0),
            countval => maxv
        );

    U2 : ENTITY work.MusicalPWM_vol(behavioral)
        PORT MAP(
            volume => control(15 DOWNTO 8),
            pulse => maxv,
            newpulse => duty
        );

    -- Process to handle the duration control. PWM is gated by an AND logic at the end only.
    P1 : PROCESS(clk, control)
    BEGIN 
        -- Reset handler
        IF (control(31) = '1') THEN
            duration <= 0;
            run_enabled <= '0';
            duration_cnt <= 0;
            status <= (OTHERS => '0');

        -- Duration controller block
        ELSIF rising_edge(clk) THEN

            -- Lock the launch to only once to prevent any incorrect operation.
            IF ((control(30) = '1') AND (run_enabled = '0')) THEN
                duration <= to_integer(unsigned(control(23 DOWNTO 16)));
                run_enabled <= '1';

            ELSE 
                -- Free the lock for the user restart
                IF ((control(30) = '0') AND (run_enabled = '1')) THEN
                    run_enabled <= '0';
                END IF;

                -- Increment the counter and set the pmw_enabled flag.
                IF (duration > 0) THEN
                    duration_cnt <= duration_cnt + 1;
                    pwm_enabled <= '1';
                ELSE
                    pwm_enabled <= '0';
                END IF;

                IF (duration_cnt >= 500_000) THEN

                    IF (duration > 0) THEN
                        duration <= duration - 1;
                        duration_cnt <= 0;
                    END IF;

                END IF;

            END IF;

            -- Mapping pwm_enabled and run_enabled to their respective bits
            status(0) <= run_enabled;
            status(1) <= pwm_enabled;

            -- Condition to detect a system mute
            IF (duty = "00000000000000000000000000000000") THEN
                status(2) <= '1';
            ELSE 
                status(2) <= '0';
            END IF;

            -- Condition to detect a 0 duration
            IF (control(23 DOWNTO 16) = "00000000") THEN
                status(3) <= '1';
            ELSE 
                status(3) <= '0';
            END IF;

            -- End of note flag
            IF (duration = 0) THEN
                status(6) <= '1';
            ELSE 
                status(6) <= '0';
            END IF;

            -- Condition to detect an invalid note (VHDL block return 0)
            IF (maxv = "00000000000000000000000000000000") THEN
                status(7) <= '1';
            ELSE 
                status(7) <= '0';
            END IF;

        END IF;

    END PROCESS;

    -- Main counter process, generate the required tone
    P2 : PROCESS (clk, control)
    BEGIN
        -- Tone generator reset handler
        IF (control(31) = '1') THEN
            act <= 0;

        -- Counter
        ELSIF rising_edge(clk) THEN
            act <= act + 1;

            -- Reset when needed
            IF (act >= to_integer(unsigned(maxv))) THEN
                act <= 0;
            END IF;

            -- Output to match the duty cycle. Gated to the pwm_enabled flag.
            IF (act < to_integer(unsigned(duty))) THEN
                pwm <= '1' AND pwm_enabled;
            ELSE
                pwm <= '0' AND pwm_enabled;
            END IF;
        END IF;

    END PROCESS;

END ARCHITECTURE;