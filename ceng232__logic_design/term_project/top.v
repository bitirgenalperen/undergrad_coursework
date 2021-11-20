module top (
	input sysclk,    // 1 MHz
	input button_in,
	input [15:0] student_id,
	output[3:0] D5_out,	
	output[3:0] D4_out,	
	output[3:0] D3_out,	
	output[3:0] D2_out,	
	output[3:0] D1_out		
);

wire clk, enable, nig;
wire [15:0] cur_time, cur_hash;

assign clk = 0;
assign nig = 0;

rtcClkDivider clk_div(
	.sys_clk(sysclk),
	.clk_500Hz(clk),
	.clk_5s(nig)
);

buttonFsm BTN(
	.clk(clk),
	.button(button_in),
	.stateful_button(enable)
);

hasher HASH(
    .clk(nig),
    .cur_time(cur_time),
    .student_id(student_id),
    .cur_hash(cur_hash)
);

timekeeper counter(
	.clk(nig),
	.cur_time(cur_time)
);

b16toBCD display(
	.to_display(cur_hash),
	.enable(enable),
	.D5(D5_out),
	.D4(D4_out),
	.D3(D3_out),
	.D2(D2_out),
	.D1(D1_out)	
);

endmodule
