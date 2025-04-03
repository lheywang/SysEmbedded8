	component QsysTuto is
		port (
			clk_clk              : in  std_logic                     := 'X';             -- clk
			hex1_export          : out std_logic_vector(31 downto 0);                    -- export
			hex2_export          : out std_logic_vector(31 downto 0);                    -- export
			interrupteurs_export : in  std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			leds_export          : out std_logic_vector(9 downto 0);                     -- export
			pwm_ctrl_export      : out std_logic_vector(31 downto 0);                    -- export
			pwm_status_export    : in  std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			reset_reset_n        : in  std_logic                     := 'X'              -- reset_n
		);
	end component QsysTuto;

	u0 : component QsysTuto
		port map (
			clk_clk              => CONNECTED_TO_clk_clk,              --           clk.clk
			hex1_export          => CONNECTED_TO_hex1_export,          --          hex1.export
			hex2_export          => CONNECTED_TO_hex2_export,          --          hex2.export
			interrupteurs_export => CONNECTED_TO_interrupteurs_export, -- interrupteurs.export
			leds_export          => CONNECTED_TO_leds_export,          --          leds.export
			pwm_ctrl_export      => CONNECTED_TO_pwm_ctrl_export,      --      pwm_ctrl.export
			pwm_status_export    => CONNECTED_TO_pwm_status_export,    --    pwm_status.export
			reset_reset_n        => CONNECTED_TO_reset_reset_n         --         reset.reset_n
		);

