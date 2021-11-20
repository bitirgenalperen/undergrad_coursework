`timescale 1ns / 1ps

module testbench_ic1500;

	// Inputs
	reg B;
	reg A;
	reg X;
	reg clk;

	// Outputs
	wire D0;
	wire D1;
	wire Q;
	wire Z;

	real result=1;//1 point bonus
	// Instantiate the Unit Under Test (UUT)
	ic1500 uut (
		.B(B), 
		.A(A), 
		.X(X),
		.clk(clk),
		.D0(D0), 
		.D1(D1), 
		.Q(Q),
		.Z(Z)
	);
    // At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial clk = 1;
	always #5 clk = ~clk;
    
	initial begin
		//$dumpfile("lab_part1.vcd");
      //$dumpvars(0,testbench_ic1500); 
		//$monitor("Time=%t | B=%b A=%b X=%b D1=%b D0=%b| Q=%b Z=%b", $time, B, A, X, D1, D0, Q, Z);
		// Initialize Inputs
		B = 0; A = 0; X = 0;
		#1;
		#10;//0
		if (D1 == 0) result = result + 0.5;
		if (D0 == 0) result = result + 0.5;
		if (Q == 0) result = result + 0.5;
		if (Z == 0) result = result + 0.5;		
		B = 0; A = 0; X = 1;
		#10;//1
		if (D1 == 0) result = result + 0.5;
		if (D0 == 1) result = result + 0.5;
		if (Q == 1) result = result + 0.5;
		if (Z == 1) result = result + 0.5;		
      B = 0; A = 1; X = 0;
		#10;//2
		if (D1 == 1) result = result + 0.5;
		if (D0 == 1) result = result + 0.5;
		if (Q == 0) result = result + 0.5;
		if (Z == 0) result = result + 0.5;		
		B = 0; A = 1; X = 1;
		#10;//3
		if (D1 == 0) result = result + 0.5;
		if (D0 == 1) result = result + 0.5;
		if (Q == 1) result = result + 0.5;
		if (Z == 1) result = result + 0.5;		
		B = 1; A = 0; X = 0;
		#10;//4
		if (D1 == 1) result = result + 0.5;
		if (D0 == 0) result = result + 0.5;
		if (Q == 1) result = result + 0.5;
		if (Z == 0) result = result + 0.5;	
		B = 1; A = 0; X = 1;
		#10;//5
		if (D1 == 0) result = result + 0.5;
		if (D0 == 1) result = result + 0.5;
		if (Q == 1) result = result + 0.5;
		if (Z == 1) result = result + 0.5;	
		B = 1; A = 1; X = 0;
		#10;//6
		if (D1 == 0) result = result + 0.5;
		if (D0 == 0) result = result + 0.5;
		if (Q == 0) result = result + 0.5;
		if (Z == 0) result = result + 0.5;	
		B = 1; A = 1; X = 1;
		#10;//7
		if (D1 == 0) result = result + 0.5;
		if (D0 == 1) result = result + 0.5;
		if (Q == 1) result = result + 0.5;
		if (Z == 1) result = result + 0.5;	
		B = 0; A = 1; X = 0;
		#10;//8
		if (D1 == 1) result = result + 0.5;
		if (D0 == 1) result = result + 0.5;
		if (Q == 0) result = result + 0.5;
		if (Z == 0) result = result + 0.5;	
		B = 0; A = 0; X = 0;
		#10;//9
		if (D1 == 0) result = result + 0.5;
		if (D0 == 0) result = result + 0.5;
		if (Q == 0) result = result + 0.5;
		if (Z == 0) result = result + 0.5;	
		B = 1; A = 0; X = 1;
		#10;//10
		if (D1 == 0) result = result + 0.5;
		if (D0 == 1) result = result + 0.5;
		if (Q == 1) result = result + 0.5;
		if (Z == 1) result = result + 0.5;	
		B = 1; A = 0; X = 0;
		#10; //11
		if (D1 == 1) result = result + 0.5;
		if (D0 == 0) result = result + 0.5;
		if (Q == 1) result = result + 0.5;
		if (Z == 0) result = result + 0.5;	
		$display("Result= %1.2f\n",result);
		#30;
		$finish;
	end
      
endmodule


