library IEEE;
use IEEE.std_logic_1164.all;

entity MusicalPWM is
port (
	-- INPUTS
	control : 	in std_logic_vector(31 downto 0);
	clk : 		in std_logic;
	
	-- OUTPUTS
	status : 	out std_logic_vector(7 downto 0);
	pwm : 		out std_logic
);
end entity;

architecture behavioral of MusicalPWM is
begin

-- To be completed... 

end architecture;