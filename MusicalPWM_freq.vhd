LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY MusicalPWM_freq IS
    PORT (
        -- INPUTS
        frequz : IN STD_LOGIC_VECTOR(7 DOWNTO 0);

        -- OUTPUTS
        countval : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
END ENTITY;

--
-- Provide the conversion for our specified values of frequencies
-- Simply return the number of clock cycle to wait to get the correct note
-- 

ARCHITECTURE behavioral OF MusicalPWM_freq IS

    -- Signals --
    SIGNAL maxval : INTEGER RANGE 0 TO 800_000;
    SIGNAL freqval : INTEGER RANGE 0 TO 255;

    -- Architecture --
BEGIN
    -- Values casts
    freqval <= to_integer(unsigned(frequz));

    -- Conditionnal cast
    maxval <=
			-- First octave
        764409 WHEN (freqval = 1)  ELSE -- Do : 65.41 Hz
        721501 WHEN (freqval = 2)  ELSE -- Dod : 69.3 Hz
        681013 WHEN (freqval = 3)  ELSE -- Re : 73.42 Hz
        642839 WHEN (freqval = 4)  ELSE -- Red : 77.78 Hz
        606722 WHEN (freqval = 5)  ELSE -- Mi : 82.41 Hz
        572672 WHEN (freqval = 6)  ELSE -- Fa : 87.31 Hz
        540541 WHEN (freqval = 7)  ELSE -- Fad : 92.5 Hz
        510204 WHEN (freqval = 8)  ELSE -- Sol : 98 Hz
        481556 WHEN (freqval = 9)  ELSE -- Sold : 103.83 Hz
        454545 WHEN (freqval = 10) ELSE -- La : 110 Hz
        429037 WHEN (freqval = 11) ELSE -- Sib : 116.54 Hz
        404957 WHEN (freqval = 12) ELSE -- Si : 123.47 Hz
		  
		  -- Second octave
        382234 WHEN (freqval = 13) ELSE -- Do : 130.81 Hz
        360776 WHEN (freqval = 14) ELSE -- Dod : 138.59 Hz
        340530 WHEN (freqval = 15) ELSE -- Re : 146.83 Hz
        321419 WHEN (freqval = 16) ELSE -- Red : 155.56 Hz
        303380 WHEN (freqval = 17) ELSE -- Mi : 164.81 Hz
        286352 WHEN (freqval = 18) ELSE -- Fa : 174.61 Hz
        270270 WHEN (freqval = 19) ELSE -- Fad : 185 Hz
        255102 WHEN (freqval = 20) ELSE -- Sol : 196 Hz
        240790 WHEN (freqval = 21) ELSE -- Sold : 207.65 Hz
        227273 WHEN (freqval = 22) ELSE -- La : 220 Hz
        214519 WHEN (freqval = 23) ELSE -- Sib : 233.08 Hz
        202478 WHEN (freqval = 24) ELSE -- Si : 246.94 Hz
		  
		  -- Second octave
        191110 WHEN (freqval = 25) ELSE -- Do : 261.63 Hz
        180388 WHEN (freqval = 26) ELSE -- Dod : 277.18 Hz
        170265 WHEN (freqval = 27) ELSE -- Re : 293.66 Hz
        160705 WHEN (freqval = 28) ELSE -- Red : 311.13 Hz
        151685 WHEN (freqval = 29) ELSE -- Mi : 329.63 Hz
        143172 WHEN (freqval = 30) ELSE -- Fa : 349.23 Hz
        135139 WHEN (freqval = 31) ELSE -- Fad : 369.99 Hz
        127551 WHEN (freqval = 32) ELSE -- Sol : 392 Hz
        120395 WHEN (freqval = 33) ELSE -- Sold : 415.3 Hz
        113636 WHEN (freqval = 34) ELSE -- La : 440 Hz
        107259 WHEN (freqval = 35) ELSE -- Sib : 466.16 Hz
        101239 WHEN (freqval = 36) ELSE -- Si : 493.88 Hz
		  
		  -- Third octave
        95557  WHEN (freqval = 37) ELSE -- Do : 523.25 Hz
        90192  WHEN (freqval = 38) ELSE -- Dod : 554.37 Hz
        85131  WHEN (freqval = 39) ELSE -- Re : 587.33 Hz
        80354  WHEN (freqval = 40) ELSE -- Red : 622.25 Hz
        75843  WHEN (freqval = 41) ELSE -- Mi : 659.26 Hz
        71586  WHEN (freqval = 42) ELSE -- Fa : 698.46 Hz
        67568  WHEN (freqval = 43) ELSE -- Fad : 739.99 Hz
        63776  WHEN (freqval = 44) ELSE -- Sol : 783.99 Hz
        60197  WHEN (freqval = 45) ELSE -- Sold : 830.61 Hz
        56818  WHEN (freqval = 46) ELSE -- La : 880 Hz
        53629  WHEN (freqval = 47) ELSE -- Sib : 932.33 Hz
        50619  WHEN (freqval = 48) ELSE -- Si : 987.77 Hz
		  
		  -- Fourth octave
        47778  WHEN (freqval = 49) ELSE -- Do : 1046.5 Hz
        45097  WHEN (freqval = 50) ELSE -- Dod : 1108.73 Hz
        42566  WHEN (freqval = 51) ELSE -- Re : 1174.66 Hz
        40176  WHEN (freqval = 52) ELSE -- Red : 1244.51 Hz
        37922  WHEN (freqval = 53) ELSE -- Mi : 1318.51 Hz
        35793  WHEN (freqval = 54) ELSE -- Fa : 1396.91 Hz
        33784  WHEN (freqval = 55) ELSE -- Fad : 1479.98 Hz
        31888  WHEN (freqval = 56) ELSE -- Sol : 1567.98 Hz
        30098  WHEN (freqval = 57) ELSE -- Sold : 1661.22 Hz
        28409  WHEN (freqval = 58) ELSE -- La : 1760 Hz
        26815  WHEN (freqval = 59) ELSE -- Sib : 1864.66 Hz
        25310  WHEN (freqval = 60) ELSE -- Si : 1975.53 Hz
		  
		  -- Fifth octave
        23889  WHEN (freqval = 61) ELSE -- Do : 2093 Hz
        22548  WHEN (freqval = 62) ELSE -- Dod : 2217.46 Hz
        21283  WHEN (freqval = 63) ELSE -- Re : 2349.32 Hz
        20088  WHEN (freqval = 64) ELSE -- Red : 2489.02 Hz
        18961  WHEN (freqval = 65) ELSE -- Mi : 2637.02 Hz
        17897  WHEN (freqval = 66) ELSE -- Fa : 2793.83 Hz
        16892  WHEN (freqval = 67) ELSE -- Fad : 2959.96 Hz
        15944  WHEN (freqval = 68) ELSE -- Sol : 3135.96 Hz
        15049  WHEN (freqval = 69) ELSE -- Sold : 3322.44 Hz
        14205  WHEN (freqval = 70) ELSE -- La : 3520 Hz
        13407  WHEN (freqval = 71) ELSE -- Sib : 3729.31 Hz
        12655  WHEN (freqval = 72) ELSE -- Si : 3951.07 Hz
		  
		  -- Sixth octave
        11945  WHEN (freqval = 73) ELSE -- Do : 4186.01 Hz
        11274  WHEN (freqval = 74) ELSE -- Dod : 4434.92 Hz
        10641  WHEN (freqval = 75) ELSE -- Re : 4696.64 Hz
        10044  WHEN (freqval = 76) ELSE -- Red : 4978.64 Hz
        9480   WHEN (freqval = 77) ELSE -- Mi : 5274.04 Hz
        8948   WHEN (freqval = 78) ELSE -- Fa : 5587.65 Hz
        8446   WHEN (freqval = 79) ELSE -- Fad : 5919.91 Hz
        7972   WHEN (freqval = 80) ELSE -- Sol : 6271.93 Hz
        7525   WHEN (freqval = 81) ELSE -- Sold : 6644.88 Hz
        7102   WHEN (freqval = 82) ELSE -- La : 7040 Hz
        6704   WHEN (freqval = 83) ELSE -- Sib : 7458.62 Hz
        6327   WHEN (freqval = 84) ELSE -- Si : 7902.13 Hz
		  
		  -- Seventh octave
        5972   WHEN (freqval = 85) ELSE -- Do : 8372.02 Hz
        5637   WHEN (freqval = 86) ELSE -- Dod : 8869.84 Hz
        5321   WHEN (freqval = 87) ELSE -- Re : 9397.28 Hz
        5022   WHEN (freqval = 88) ELSE -- Red : 9956.06 Hz
        4740   WHEN (freqval = 89) ELSE -- Mi : 10548.08 Hz
        4474   WHEN (freqval = 90) ELSE -- Fa : 11175.3 Hz
        4223   WHEN (freqval = 91) ELSE -- Fad : 11839.82 Hz
        3986   WHEN (freqval = 92) ELSE -- Sol : 12543.86 Hz
        3762   WHEN (freqval = 93) ELSE -- Sold : 13289.76 Hz
        3551   WHEN (freqval = 94) ELSE -- La : 14080 Hz
        3352   WHEN (freqval = 95) ELSE -- Sib : 14917.24 Hz
		  3164   WHEN (freqval = 96) ELSE -- Si : 15804.26 Hz
		  
		  -- Default case
        0; -- Nothing

    -- Final assignement of the value
    countval <= STD_LOGIC_VECTOR(to_unsigned(maxval, countval'length));

END ARCHITECTURE behavioral;