`timescale 1ns / 1ps
module PharmacyMem(
    input [4:0] studentID ,
    input clk,
    input [1:0] mode , // 0: list, 2: checkIn, 3: delete
    input [7:0] checkInTime,
    output reg [4:0] listOutput,
    output reg listBusy ,
    output reg ready
	);
reg [12:0]holder[10:0];//holds checkin time and id in order
integer node,k,num;

initial begin
	num = 1; ready = 1; listBusy = 0; k=1;
    for (node=0; node<=10; node=node+1) begin holder[node] = 0; end  
end

always@(posedge clk)begin
	if((num<=10)&&(mode == 2))begin
		ready = 1; listBusy = 0; k=1;
		for (node = num; checkInTime < holder[node/2][12:8]; node = node/2) begin holder[node] <= holder[node/2]; end
		holder[node][7:0] <= studentID;
		holder[node][12:8] <= checkInTime;
		num <= num + 1; end
	
	else if((num>1)&&(mode == 3))begin
		ready = 1; listBusy = 0; k=1;
		num <= num -1;
	
		for (node=1; (2*node < num -1) && ((holder[num -1][12:8] > holder[2*node+1][12:8])  || (holder[num -1][12:8] > holder[2*node][12:8])) ; node = (holder[2*node][12:8] > holder[2*node+1][12:8] ? 2*node+1 : 2*node)) begin
			if ((holder[num -1][12:8] > holder[2*node+1][12:8])  && (2*node+1 == num -1  || holder[2*node+1][12:8] > holder[2*node][12:8])) begin holder[node] <= holder[2*node]; end
			else if ((holder[num -1][12:8] > holder[2*node][12:8])) begin holder[node] <= holder[2*node+1]; end
		end
		holder[node] = holder[num -1]; end
	
	else if((num>1)&&(mode == 0))begin
		if (ready && ~listBusy) begin
			listOutput = holder[1][7:0];
			listBusy = 1; ready = 0; k = 2;
		end
		else begin
			if (k < num) begin
				listOutput = holder[k][7:0];
				k <= k + 1;
			end 
			else begin ready = 1; listBusy = 0; k=1; end end end end
endmodule
