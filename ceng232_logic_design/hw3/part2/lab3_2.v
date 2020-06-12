`timescale 1ns / 1ps
`define modulus(arg1,arg0,pos) \
	if(arg0+pos>=10)\
		begin\
		arg1 = 1-arg1;\
		arg0 = arg0+pos-10;\
		end\
	else\
		begin\
		arg0 = arg0+pos;\
		end\
		
module lab3_2(
			input[3:0] command,
			input CLK, 
			input mode,
			output reg [7:0] total_time1,
			output reg [7:0] total_time0,
			output reg [7:0] total_cost1,
			output reg [7:0] total_cost0,
			output reg [3:2] coord_x,
			output reg [1:0] coord_y,
			output reg warning
    );
	
	initial begin
        total_cost1 = 0; total_cost0 = 0;
	total_time1 = 0; total_time0 = 0;
	coord_x = 1; coord_y = 1;
	warning=0; end
	
	always@(posedge CLK) begin
		if(mode == 1) begin
			total_cost1 = 0; total_cost0 = 0;
			total_time1 = 0; total_time0 = 0;
			coord_x = 0; coord_y = 0;
			warning=1; end
				
		else if(mode==0) begin
			warning = 0;
			`modulus(total_time1,total_time0,1);
			if(command == 0) begin `modulus(total_cost1,total_cost0,1); end
					
			else if(command == 2)begin
			`modulus(total_cost1,total_cost0,2);
			if(coord_y ==2) coord_y=0;
			else coord_y=coord_y+1; end
					
			else if(command == 6) begin
			`modulus(total_cost1,total_cost0,2);
			if(coord_y ==0)coord_y=2;
			else coord_y=coord_y-1; end
					
			else if(command == 4) begin
			`modulus(total_cost1,total_cost0,2);
			if(coord_x ==2)coord_x=0;
			else coord_x=coord_x+1; end
			
			else if(command == 8) begin
			`modulus(total_cost1,total_cost0,2);
			if(coord_x ==0)coord_x=2;
			else coord_x=coord_x-1; end
					
			else if(command == 1)begin
			if((coord_x ==0 && (coord_y == 0 | coord_y == 1 | coord_y == 2))|(coord_y ==2 && (coord_x == 0 | coord_x == 1 | coord_x == 2))) begin
			`modulus(total_cost1,total_cost0,1); end
			else begin
			`modulus(total_cost1,total_cost0,3);
			coord_x=coord_x-1;
			coord_y=coord_y+1; end 	
			end
					
			else if(command == 3) begin
			if((coord_x ==2 && (coord_y == 0 | coord_y == 1 | coord_y == 2))|(coord_y ==2 && (coord_x == 0 | coord_x == 1 | coord_x == 2))) begin
			`modulus(total_cost1,total_cost0,1); end
			else begin
			`modulus(total_cost1,total_cost0,3);
			coord_x=coord_x+1;
			coord_y=coord_y+1; end 	
			end
					
			else if(command == 5) begin
			if((coord_x ==2 && (coord_y == 0 || coord_y == 1 || coord_y == 2))|(coord_y ==0 && (coord_x == 0 || coord_x == 1 || coord_x == 2))) begin
			`modulus(total_cost1,total_cost0,1); end
			else begin
			`modulus(total_cost1,total_cost0,3);
			coord_x=coord_x+1;
			coord_y=coord_y-1; end 	
			end
					
			else if(command == 7) begin
			if((coord_x ==0 && (coord_y == 0 | coord_y == 1 | coord_y == 2))|(coord_y ==0 && (coord_x == 0 | coord_x == 1 || coord_x == 2))) begin
			`modulus(total_cost1,total_cost0,1); end
			else begin
			`modulus(total_cost1,total_cost0,3);
			coord_x=coord_x-1;
			coord_y=coord_y-1; end 	
			end																			
			end
			end
endmodule
