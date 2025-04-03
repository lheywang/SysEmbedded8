LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY MusicalPWM_vol IS
    PORT (
        -- INPUTS
        volume : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        pulse : IN STD_LOGIC_VECTOR(31 DOWNTO 0);

        -- OUTPUTS
        newpulse : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
END ENTITY;

--
-- Provide the conversion for our specified values of volumes
-- Always divide by two, and then apply volume, which scale down the value
--
-- The duty cycle is then 50% for the max volume
-- Variable for smaller volumes (between 0 and 255)
-- 

ARCHITECTURE behavioral OF MusicalPWM_vol IS

    -- Signals --
    SIGNAL maxval : INTEGER RANGE 0 TO 3_000_000; -- Large enough to handle temp vals
    SIGNAL volval : INTEGER RANGE 0 TO 255;

    -- Architecture --

BEGIN
    -- Compute the volume
    maxval <= (to_integer(unsigned(pulse)) * to_integer(unsigned(volume))) / 511;

    -- Final assignement of the value
    newpulse <= STD_LOGIC_VECTOR(to_unsigned(maxval, newpulse'length));

END ARCHITECTURE behavioral;