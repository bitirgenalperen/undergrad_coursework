`timescale 1ns / 1ps

module lab3_2_testbench;

	// Inputs
	reg [3:0] command;
	reg CLK;
	reg mode;

	// Outputs
	wire [7:0] total_time1;
	wire [7:0] total_time0;
	wire [7:0] total_cost1;
	wire [7:0] total_cost0;
	wire [3:2] coord_x;
	wire [1:0] coord_y;
	wire warning;
	
	real result=1.5;//1.5 point bonus
	// Instantiate the Unit Under Test (UUT)
	lab3_2 uut (
		.command(command), 
		.CLK(CLK), 
		.mode(mode), 
		.total_time1(total_time1), 
		.total_time0(total_time0), 
		.total_cost1(total_cost1), 
		.total_cost0(total_cost0), 
		.coord_x(coord_x),
		.coord_y(coord_y),
		.warning(warning)
	);
    // At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial CLK = 0;
	always #5 CLK = ~CLK;
    
	initial begin
		// Initialize Inputs
		//$dumpfile("test.vcd");
      //$dumpvars(0,lab3_2_testbench);
		command = 4'b0000;
		mode = 0;
		#6;
      // set monitor to inputs and outputs
		//$monitor("Time=%t | command=%b mode=%b coord_x=%b coord_y=%b total_cost1=%d total_cost0=%d total_time1=%d total_time0=%d warning=%b", $time, command, mode, coord_x, coord_y, total_cost1, total_cost0, total_time1, total_time0, warning);
		// Add stimulus here
		//1
		if (coord_x == 2'b01 && coord_y == 2'b01) result = result + 1;
		if (total_cost1==0 && total_cost0==1) result = result + 1;
		if (total_time1==0 && total_time0==1) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0001;
		mode = 0;
		#10; // Wait for clock edge
		//2
		if (coord_x == 2'b00 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==4) result = result + 1;
		if (total_time1==0 && total_time0==2) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0111;
		mode = 0;
		#10;
		//3
		if (coord_x == 2'b00 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==5) result = result + 1;
		if (total_time1==0 && total_time0==3) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0010;
		mode = 0;
		#10;
		//4
		if (coord_x == 2'b00 && coord_y == 2'b00) result = result + 1;
		if (total_cost1==0 && total_cost0==7) result = result + 1;
		if (total_time1==0 && total_time0==4) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0011;
		mode = 1;
		#10;
		//5
		if (coord_x == 2'b00 && coord_y == 2'b00) result = result + 1;
		if (total_cost1==0 && total_cost0==0) result = result + 1;
		if (total_time1==0 && total_time0==0) result = result + 1;
		if (warning==1) result = result + 0.5;
		command= 4'b0011;
		mode = 0;
		#10;
		//6
		if (coord_x == 2'b01 && coord_y == 2'b01) result = result + 1;
		if (total_cost1==0 && total_cost0==3) result = result + 1;
		if (total_time1==0 && total_time0==1) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0011;
		mode = 0;
		#10;
		//7
		if (coord_x == 2'b10 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==6) result = result + 1;
		if (total_time1==0 && total_time0==2) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0111;
		mode = 0;
		#10;
		//8
		if (coord_x == 2'b01 && coord_y == 2'b01) result = result + 1;
		if (total_cost1==0 && total_cost0==9) result = result + 1;
		if (total_time1==0 && total_time0==3) result = result + 1;
		if (warning==0) result = result + 0.5;		
		command= 4'b0111;
		mode = 0;
		#10;
		//9
		if (coord_x == 2'b00 && coord_y == 2'b00) result = result + 1;
		if (total_cost1==1 && total_cost0==2) result = result + 1;
		if (total_time1==0 && total_time0==4) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0011;
		mode = 0;
		#10;
		//10
		if (coord_x == 2'b01 && coord_y == 2'b01) result = result + 1;
		if (total_cost1==1 && total_cost0==5) result = result + 1;
		if (total_time1==0 && total_time0==5) result = result + 1;
		if (warning==0) result = result + 0.5;		
		command= 4'b0011;
		mode = 0;
		#10;
		//11
		if (coord_x == 2'b10 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==1 && total_cost0==8) result = result + 1;
		if (total_time1==0 && total_time0==6) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0111;
		mode = 0;
		#10;
		//12
		if (coord_x == 2'b01 && coord_y == 2'b01) result = result + 1;
		if (total_cost1==0 && total_cost0==1) result = result + 1;
		if (total_time1==0 && total_time0==7) result = result + 1;
		if (warning==0) result = result + 0.5;	
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;
		command= 4'b0111;
		mode = 0;
		#10;//190 saniye aynı komut attık
		//13
		if (coord_x == 2'b00 && coord_y == 2'b00) result = result + 1;
		if (total_cost1==0 && total_cost0==2) result = result + 1;
		if (total_time1==0 && total_time0==6) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0110;
		mode = 0;
		#10;
		//14
		if (coord_x == 2'b00 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==4) result = result + 1;
		if (total_time1==0 && total_time0==7) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b1000;
		mode = 0;
		#10;
		//15
		if (coord_x == 2'b10 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==6) result = result + 1;
		if (total_time1==0 && total_time0==8) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0101;
		mode = 0;
		#10;
		//16
		if (coord_x == 2'b10 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==7) result = result + 1;
		if (total_time1==0 && total_time0==9) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b1010;
		mode = 0;
		#10;
		//17
		if (coord_x == 2'b10 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==7) result = result + 1;
		if (total_time1==1 && total_time0==0) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b1111;
		mode = 0;
		#10;
		//18
		if (coord_x == 2'b10 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==7) result = result + 1;
		if (total_time1==1 && total_time0==1) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0000;
		mode = 0;
		#10;
		//19
		if (coord_x == 2'b10 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==0 && total_cost0==8) result = result + 1;
		if (total_time1==1 && total_time0==2) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0100;
		mode = 0;
		#10;
		//20
		if (coord_x == 2'b00 && coord_y == 2'b10) result = result + 1;
		if (total_cost1==1 && total_cost0==0) result = result + 1;
		if (total_time1==1 && total_time0==3) result = result + 1;
		if (warning==0) result = result + 0.5;
		command= 4'b0000;
		mode = 1;
		#10;
		//21
		if (coord_x == 2'b00 && coord_y == 2'b00) result = result + 1;
		if (total_cost1==0 && total_cost0==0) result = result + 1;
		if (total_time1==0 && total_time0==0) result = result + 1;
		if (warning==1) result = result + 0.5;
		$display("Result= %1.2f\n",result);
		#10;
		$finish;
		
	end
      
endmodule
