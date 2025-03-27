	component QsysTuto is
		port (
			clk_clk                  : in  std_logic                     := 'X';             -- clk
			reset_reset_n            : in  std_logic                     := 'X';             -- reset_n
			interrupteurs_export     : in  std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			boutons_poussoirs_export : in  std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			leds_export              : out std_logic_vector(9 downto 0);                     -- export
			hex_export               : out std_logic_vector(31 downto 0)                     -- export
		);
	end component QsysTuto;

	u0 : component QsysTuto
		port map (
			clk_clk                  => CONNECTED_TO_clk_clk,                  --               clk.clk
			reset_reset_n            => CONNECTED_TO_reset_reset_n,            --             reset.reset_n
			interrupteurs_export     => CONNECTED_TO_interrupteurs_export,     --     interrupteurs.export
			boutons_poussoirs_export => CONNECTED_TO_boutons_poussoirs_export, -- boutons_poussoirs.export
			leds_export              => CONNECTED_TO_leds_export,              --              leds.export
			hex_export               => CONNECTED_TO_hex_export                --               hex.export
		);

