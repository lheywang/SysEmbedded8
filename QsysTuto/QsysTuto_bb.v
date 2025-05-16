
module QsysTuto (
	clk_clk,
	hex1_export,
	hex2_export,
	interrupteurs_export,
	leds_export,
	pwm_ctrl_export,
	pwm_status_export,
	reset_reset_n);	

	input		clk_clk;
	output	[31:0]	hex1_export;
	output	[31:0]	hex2_export;
	input	[9:0]	interrupteurs_export;
	output	[9:0]	leds_export;
	output	[31:0]	pwm_ctrl_export;
	input	[7:0]	pwm_status_export;
	input		reset_reset_n;
endmodule
