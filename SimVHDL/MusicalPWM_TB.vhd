LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;

ENTITY MusicalPWM_TB IS
END ENTITY MusicalPWM_TB;

ARCHITECTURE behavioral OF MusicalPWM_TB IS

    SIGNAL CLK_TB : STD_LOGIC := '0';
    SIGNAL CONTROL_TB : STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL STATUS_TB : STD_LOGIC_VECTOR(7 DOWNTO 0);
    SIGNAL PWM_TB : STD_LOGIC;
BEGIN

    U1 : ENTITY work.MusicalPWM(behavioral)
        PORT MAP(
            control => CONTROL_TB,
            clk => CLK_TB,
            status => STATUS_TB,
            pwm => PWM_TB
        );

    P1 : PROCESS
    BEGIN 
        CLK_TB <= not CLK_TB;
        wait for 10 ns;
    END PROCESS;

    P2 : PROCESS
    BEGIN
        CONTROL_TB <= "11000000000101000111111100000001";
        wait for 100 ns;
        CONTROL_TB <= "10000000000101000111111100000001";
        wait for 500 ms;
        CONTROL_TB <= "11000000000101000111111100000001";
        wait for 100 ns;
        CONTROL_TB <= "10000000000101000111111100000001";
        wait for 500 ms;
    END PROCESS;
    
END ARCHITECTURE behavioral;
