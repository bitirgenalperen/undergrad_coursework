`timescale 1ns / 1ps

module testbench_AddParity(
    );
	 
	reg [1:8] dataIn;
	wire [1:12] dataOut;
	integer result=0;
	
	//instances
	AddParity ins( dataIn,   dataOut);	
	
	initial begin
	$display("Starting Testbench");
#1;
	dataIn=8'b00111011;
	#1;
	if (dataOut==12'b110101111011) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b110101111011);
	
	#1;
	dataIn=8'b01000100;
	#1;
	if (dataOut==12'b110110010100) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b110110010100);
	
	#1;
	dataIn=8'b01001001;
	#1;
	if (dataOut==12'b000010001001) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b000010001001);
	
	#1;
	dataIn=8'b01010110;
	#1;
	if (dataOut==12'b110010100110) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b110010100110);
	
	#1;
	dataIn=8'b01011011;
	#1;
	if (dataOut==12'b000110111011) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b000110111011);
	
	#1;
	dataIn=8'b01100100;
	#1;
	if (dataOut==12'b100011010100) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b100011010100);
	
	#1;
	dataIn=8'b01101001;
	#1;
	if (dataOut==12'b010111001001) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b010111001001);
	
	#1;
	dataIn=8'b01110110;
	#1;
	if (dataOut==12'b100111100110) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b100111100110);
	
	#1;
	dataIn=8'b01111011;
	#1;
	if (dataOut==12'b010011111011) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b010011111011);
	
	#1;
	dataIn=8'b10000100;
	#1;
	if (dataOut==12'b101000010100) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b101000010100);
	
	#1;
	dataIn=8'b10001000;
	#1;
	if (dataOut==12'b011000011000) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b011000011000);
	
	#1;
	dataIn=8'b10010111;
	#1;
	if (dataOut==12'b101000110111) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b101000110111);
	
	#1;
	dataIn=8'b10011010;
	#1;
	if (dataOut==12'b011100101010) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b011100101010);
	
	#1;
	dataIn=8'b10100101;
	#1;
	if (dataOut==12'b111001000101) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b111001000101);
	
	#1;
	dataIn=8'b10101000;
	#1;
	if (dataOut==12'b001101011000) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b001101011000);
	
	#1;
	dataIn=8'b10110110;
	#1;
	if (dataOut==12'b111001100110) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b111001100110);
	
	#1;
	dataIn=8'b10111011;
	#1;
	if (dataOut==12'b001101111011) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b001101111011);
	
	#1;
	dataIn=8'b11000100;
	#1;
	if (dataOut==12'b001110010100) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b001110010100);
	
	#1;
	dataIn=8'b11001001;
	#1;
	if (dataOut==12'b111010001001) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b111010001001);
	
	#1;
	dataIn=8'b11010110;
	#1;
	if (dataOut==12'b001010100110) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b001010100110);
	
	#1;
	dataIn=8'b11011010;
	#1;
	if (dataOut==12'b111010101010) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b111010101010);
	
	#1;
	dataIn=8'b11100101;
	#1;
	if (dataOut==12'b011111000101) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b011111000101);
	
	#1;
	dataIn=8'b11101000;
	#1;
	if (dataOut==12'b101011011000) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b101011011000);
	
	#1;
	dataIn=8'b11110111;
	#1;
	if (dataOut==12'b011011110111) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b011011110111);
	
	#1;
	dataIn=8'b11111010;
	#1;
	if (dataOut==12'b101111101010) result=result+4;
		else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",dataIn,dataOut,12'b101111101010);
	
	   
	
	$display("Result is:%d",result);
	$finish;
	end

endmodule
