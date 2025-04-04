LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY MusicalPWM IS
    PORT (
        -- INPUTS
        control : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        clk : IN STD_LOGIC;

        -- OUTPUTS
        status : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)   := "00000000";
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

    -- Process to copy the data, and launch the duration counter
    P1 : PROCESS(clk, control)
    BEGIN 
        IF (control(31) = '1') THEN
            duration <= 0;
            run_enabled <= '0';
            duration_cnt <= 0;
            status <= (OTHERS => '0');

        ELSIF rising_edge(clk) THEN
            IF (control(30) = '1' AND run_enabled = '0') THEN
                duration <= to_integer(unsigned(control(23 DOWNTO 16)));
                run_enabled <= '1';
                status(0) <= '1';   -- Signify to the user that a relaod is required.

            ELSE 
                -- Free the lock for the user restart
                IF (control(30) = '0') THEN
                    run_enabled <= '0';
                    status(0) <= '0';
                END IF;

                IF (duration > 0) THEN
                    duration_cnt <= duration_cnt + 1;
                    pwm_enabled <= '1' AND pwm_enabled;
                else
                    pwm_enabled <= '0' AND pwm_enabled;
                END IF;

                IF (duration_cnt >= 500_000) THEN
                    IF (duration > 0) THEN
                        duration <= duration - 1;
                        duration_cnt <= 0;
                    else
                        duration <= 0;
                        duration_cnt <= 0;
                    END IF;
                END IF;

            END IF;

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
        IF (control(31) = '1') THEN
            act <= 0;

        ELSIF rising_edge(clk) THEN

            IF (duration > 0) THEN
                act <= act + 1;

                IF (act >= to_integer(unsigned(maxv))) THEN
                    act <= 0;
                END IF;

                IF (act < to_integer(unsigned(duty))) THEN
                    pwm <= '1';
                ELSE
                    pwm <= '0';
                END IF;

            END IF;

        END IF;

    END PROCESS;

END ARCHITECTURE;