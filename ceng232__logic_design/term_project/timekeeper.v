module timekeeper (
	input clk,    // Clock
	output[15:0] cur_time	
);
reg [15:0]holder;
initial begin holder = 0; end

assign cur_time = holder;

always@(posedge clk)begin
if(cur_time==65535)begin holder <= 0;end
else begin holder <= holder+1; end
end

endmodule
