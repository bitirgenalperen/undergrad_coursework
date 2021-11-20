`timescale 1ns / 1ps
module testbench_SEC_MEM(
    );
	reg clk;
	reg [1:12] dataIn;
	reg mode; //0:read, 1:write
	reg [3:0] addr;
	wire  [1:12] dataOut;
	integer result=0;
	reg initiallyEmpty=1'b1;

	integer i;
	//instances
	SEC_MEM ins( dataIn , clk , mode , addr , dataOut );	

	//Set initial values
	initial clk = 0;	
	always #5 clk = ~clk;
  
  initial begin
	$display("Starting Testbench");

	  //read initial values
		#1 //_1
		$display("Reading Initial Values");
		mode=1'b0;			
		for(i=0;i<=15;i=i+1)
		begin
			addr = i;
			#10;
			if (dataOut!==0) initiallyEmpty=0;
		end
		#1; //_2
		if (initiallyEmpty==1'b1) result=result+4;
			else $display("Memory should be initially empty..");
		
		
		//write operation: inputs that have 1-bit error in one of the bits.
		#1;		
		mode=1'b1; /*WRITE mode*/			

		addr=0;
		dataIn=12'b010101111011;
		#10;

		addr=1;
		dataIn=12'b100110010100;
		#10;

		addr=2;
		dataIn=12'b001010001001;
		#10;

		addr=3;
		dataIn=12'b110110100110;
		#10;

		addr=4;
		dataIn=12'b000100111011;
		#10;

		addr=5;
		dataIn=12'b100010010100;
		#10;

		addr=6;
		dataIn=12'b010111101001;
		#10;

		addr=7;
		dataIn=12'b100111110110;
		#10;

		addr=8;
		dataIn=12'b010011110011;
		#10;

		addr=9;
		dataIn=12'b101000010000;
		#10;

		addr=10;
		dataIn=12'b011000011010;
		#10;

		addr=11;
		dataIn=12'b101000110110;
		#10;

		addr=12;
		dataIn=12'b011100101010;
		#10;

		addr=13;
		dataIn=12'b011001000101;
		#10;

		addr=14;
		dataIn=12'b011101011000;
		#10;

		addr=15;
		dataIn=12'b110001100110;
		#10;



		//read operation
		$display($time,"Read 16 memory values");
		#1
		mode=1'b0;	/*READ mode*/ 		

		addr=0;
		#9;
		if(dataOut==12'b110101111011) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b010101111011,dataOut,12'b110101111011);
		#1;
		addr=1;
		#9;
		if(dataOut==12'b110110010100) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b100110010100,dataOut,12'b110110010100);
		#1;
		addr=2;
		#9;
		if(dataOut==12'b000010001001) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b001010001001,dataOut,12'b000010001001);
		#1;
		addr=3;
		#9;
		if(dataOut==12'b110010100110) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b110110100110,dataOut,12'b110010100110);
		#1;
		addr=4;
		#9;
		if(dataOut==12'b000110111011) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b000100111011,dataOut,12'b000110111011);
		#1;
		addr=5;
		#9;
		if(dataOut==12'b100011010100) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b100010010100,dataOut,12'b100011010100);
		#1;
		addr=6;
		#9;
		if(dataOut==12'b010111001001) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b010111101001,dataOut,12'b010111001001);
		#1;
		addr=7;
		#9;
		if(dataOut==12'b100111100110) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b100111110110,dataOut,12'b100111100110);
		#1;
		addr=8;
		#9;
		if(dataOut==12'b010011111011) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b010011110011,dataOut,12'b010011111011);
		#1;
		addr=9;
		#9;
		if(dataOut==12'b101000010100) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b101000010000,dataOut,12'b101000010100);
		#1;
		addr=10;
		#9;
		if(dataOut==12'b011000011000) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b011000011010,dataOut,12'b011000011000);
		#1;
		addr=11;
		#9;
		if(dataOut==12'b101000110111) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b101000110110,dataOut,12'b101000110111);
		#1;
		addr=12;
		#9;
		if(dataOut==12'b011100101010) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b011100101010,dataOut,12'b011100101010);
		#1;
		addr=13;
		#9;
		if(dataOut==12'b111001000101) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b011001000101,dataOut,12'b111001000101);
		#1;
		addr=14;
		#9;
		if(dataOut==12'b001101011000) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b011101011000,dataOut,12'b001101011000);
		#1;
		addr=15;
		#9;
		if(dataOut==12'b111001100110) result=result+6;
			else $display("time:",$time,":Error in result. For dataIn:%b,  dataOut:%b should be %b",12'b110001100110,dataOut,12'b111001100110);
		#1;

		
		$display("Result is:%d",result);
		$finish;
	end


endmodule
