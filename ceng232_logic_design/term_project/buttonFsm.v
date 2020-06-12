module buttonFsm (
	input clk,
	input button,    
	output stateful_button
);
reg str;
reg en;

initial begin str = 0; en = 0; end
assign stateful_button = (~str && (button ^ en))||(str && en);

always@(posedge clk) begin
	str <= button;
	en <= (~str && (button ^ en))||(str && en);
	 end 
endmodule
