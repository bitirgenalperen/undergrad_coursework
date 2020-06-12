`timescale 1ns / 1ps

module AddParity(
input [1:8] dataIn,
output reg [1:12] dataOut
);
always@(*)
begin

dataOut[1] = dataIn[1]^dataIn[2]^dataIn[4]^dataIn[5]^dataIn[7];
dataOut[2] = dataIn[1]^dataIn[3]^dataIn[4]^dataIn[6]^dataIn[7];
dataOut[4] = dataIn[2]^dataIn[3]^dataIn[4]^dataIn[8];
dataOut[8] = dataIn[5]^dataIn[6]^dataIn[7]^dataIn[8];
dataOut[3] = dataIn[1];
dataOut[5] = dataIn[2];
dataOut[6] = dataIn[3];
dataOut[7] = dataIn[4];
dataOut[9] = dataIn[5];
dataOut[10] = dataIn[6];
dataOut[11] = dataIn[7];
dataOut[12] = dataIn[8];

end
endmodule

module CheckParity(
input [1:12] dataIn,
output reg [1:8] dataOut
);
wire [1:4]C;
reg [1:12]data;

assign C[4] = dataIn[1]^dataIn[3]^dataIn[5]^dataIn[7]^dataIn[9]^dataIn[11];
assign C[3] = dataIn[2]^dataIn[3]^dataIn[6]^dataIn[7]^dataIn[10]^dataIn[11];
assign C[2] = dataIn[4]^dataIn[5]^dataIn[6]^dataIn[7]^dataIn[12];
assign C[1] = dataIn[8]^dataIn[9]^dataIn[10]^dataIn[11]^dataIn[12];

always@(*)begin
data = dataIn;
if(C!=0000) begin data[C] = ~data[C]; end

dataOut[1] = data[3];
dataOut[2] = data[5];
dataOut[3] = data[6];
dataOut[4] = data[7];
dataOut[5] = data[9];
dataOut[6] = data[10];
dataOut[7] = data[11];
dataOut[8] = data[12];
end
 
endmodule


module RAM(
input [7:0] dataIn, //0:read, 1:write
input clk,
input mode,
input [3:0] addr,
output reg [7:0] dataOut);

reg holder[15:0][7:0];

integer i,j;
initial begin
  for (i=0;i<=15;i=i+1) begin
    for(j=0;j<=7;j=j+1) begin
    holder[i][j] = 0;
    end
    end
end

always@(posedge clk) begin

if(mode==0)begin
for(i=0;i<=7;i=i+1) begin
dataOut[i] = holder[addr][i];
end
end


else if(mode==1)begin
for(i=0;i<=7;i=i+1) begin
holder[addr][i] = dataIn[i];
end
end

end
endmodule

module SEC_MEM(
input [1:12] dataIn,
input clk,
input mode, //0:read, 1:write
input [3:0] addr,
output  [1:12] dataOut);

//DO NOT EDIT THIS MODULE
wire  [7:0]  ramDataIn;
wire  [7:0]  ramDataOut;
CheckParity CP(dataIn,ramDataIn);
RAM RM(ramDataIn, clk, mode, addr, ramDataOut);
AddParity AP(ramDataOut,dataOut);

endmodule
