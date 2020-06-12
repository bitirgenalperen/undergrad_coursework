module rtcClkDivider (
	input sys_clk,    // 1 MHz
	output clk_500Hz, // 500 Hz
	output clk_5s  // 0.2 Hz
);

parameter KEYCHANGE_PERIOD = 0.001;  // DO NOT CHANGE THE NAME OF THIS PARAMETER 
// AND MAKE SURE TO USE THIS PARAMETER INSTEAD OF HARDCODING OTHER VALUES
reg [0:11] re_500;
integer re_5;

initial re_500 = 0;
initial re_5 = 0;

assign clk_500Hz = 1000 <= re_500;
assign clk_5s = 250 * 2000 * KEYCHANGE_PERIOD <= re_5;

always@(posedge sys_clk)
begin

	if(re_5 == 500 * 2000 * KEYCHANGE_PERIOD-1)begin
		re_5 <= 0; 
	end
	else begin
		re_5 <= re_5 +1;
	end
	if(re_500 == 1999) begin
		re_500 <= 0;
	end
	else begin
		re_500 <= re_500 +1;
	end

end
	
endmodule


