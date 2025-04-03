LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY MusicalPWM IS
    PORT (
        -- INPUTS
        control : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        clk : IN STD_LOGIC;

        -- OUTPUTS
        status : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
        pwm : OUT STD_LOGIC
    );
END ENTITY;

ARCHITECTURE behavioral OF MusicalPWM IS

    -- Signals --
    -- Configurations vectors
    SIGNAL maxv : STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL duty : STD_LOGIC_VECTOR(31 DOWNTO 0);

    -- Counter signal
    SIGNAL act : INTEGER RANGE 0 to 800_000;

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

    -- Then, enter the main loop
    P2 : PROCESS (clk, control)
    BEGIN
        IF (control(7) = '1') THEN
            act <= 0;

        ELSIF rising_edge(clk) THEN
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

    END PROCESS;

END ARCHITECTURE;