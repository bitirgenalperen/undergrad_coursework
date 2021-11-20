module hasher (
	input clk,    // Clock
	input [15:0] cur_time,
	input [15:0] student_id,
	output [15:0] cur_hash	
);
reg [31:0] prev_hash;
initial begin prev_hash = 0;end

always@(posedge clk) begin
    prev_hash <= (((((cur_time ^ student_id) - prev_hash) *((cur_time ^ student_id) - prev_hash)) >> 8) & 16'hFFFF);
    end
assign cur_hash = prev_hash[15:0];  
endmodule
