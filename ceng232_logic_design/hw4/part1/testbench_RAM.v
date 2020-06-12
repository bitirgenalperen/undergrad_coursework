`timescale 1ns / 1ps

module testbench_RAM(
    );
	reg CLK;
	reg  [7:0] ramInput;
	reg mode;//0:read, 1:write
	reg [3:0] addr;
	wire [7:0] ramOutput;
	integer i;
	integer result=0;
	reg initiallyEmpty=1'b1;
	//instances
	RAM ins( ramInput , CLK , mode , addr , ramOutput );	
	
	
	
	//Set initial values
	initial CLK = 0;	
	always #5 CLK = ~CLK;
  
	initial begin
	//initialize all inputs to zero
	
	$display("Starting Testbench");
		//read initial values
		mode=1'b0;			
		for(i=0;i<=15;i=i+1)
		begin
			addr = i;
			#10
			if (ramOutput!==0) initiallyEmpty=0;
		end 
		#1; //_2
		if (initiallyEmpty==1'b1) result=result+4;
			else $display("Memory should be initially empty..");
		#1
		//write operation
		mode=1'b1;			
		for(i=0;i<=15;i=i+1)
		begin
			ramInput=i+1;
			addr = i;
			#10;
		end
		//read operation
		#1
		mode=1'b0;			
		for(i=0;i<=15;i=i+1)
		begin
			addr = i;
			#10;
			if (ramOutput==(i+1)) result=result+6;
			else $display("time:",$time,":Error in reading value, address %b value %b should be %d",addr,ramOutput,i+1);
		end
		$display("Result is:%d",result);
		$finish;
	end
		
endmodule
