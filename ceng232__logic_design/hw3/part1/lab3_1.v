module sf(
    input S,
    input F,
    input clk,
    output reg Q
    );
    initial begin
        Q = 0;
    end
	always@(posedge clk)
 		begin

			if((S==0)&&(F==0))Q=0;
			else if((S==0)&&(F==1))Q=1;
			else if((S==1)&&(F==1))Q=~Q;
			else Q=Q;

		end	
    // write your code here
	 
endmodule


module ic1500(
    input B, 
    input A, 
    input X, 
	 input clk,
	 output D0,
	 output D1,
	 output Q,
    output Z
    );
    // write your code here
	assign D0 = X|(A&~B);		
	assign D1 = (A&~B&~X)|(~A&B&~X);
	sf sf_1(D1,D0,clk,Q);
	assign Z = Q&X;
endmodule
