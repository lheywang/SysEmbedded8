
module QsysTuto (
	clk_clk,
	reset_reset_n,
	interrupteurs_export,
	boutons_poussoirs_export,
	leds_export,
	hex_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[9:0]	interrupteurs_export;
	input	[1:0]	boutons_poussoirs_export;
	output	[9:0]	leds_export;
	output	[31:0]	hex_export;
endmodule
