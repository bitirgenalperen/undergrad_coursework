`timescale 1ns / 1ps
module testbench(
    );
    reg [4:0] studentID,studentID2;
    reg clk;
    reg[1:0] mode,mode2; // 0: list, 2: checkIn, 3: delete
    reg [7:0] checkInTime,checkInTime2;
    wire [4:0] listOutput,listOutput2;
    wire listBusy,listBusy2;
    wire ready,ready2;
    integer result=0;
    integer inputList [1:10];
    reg [4:0] outputList1 [1:10];
    reg [4:0] outputList2 [1:7];
    integer deleteMinOk=1;
    integer minHeapOk=1;
    integer i;
    
    //Instance of the Module
    PharmacyMem INSTANCE1(studentID, clk, mode, checkInTime, listOutput, listBusy, ready);
    PharmacyMem INSTANCE2(studentID2, clk, mode2, checkInTime2, listOutput2, listBusy2, ready2);
    //Set initial values
    initial begin
        clk = 0;	
        inputList[1]=11;
        inputList[2]=10;
        inputList[3]=9;
        inputList[4]=6;
        inputList[5]=7;
        inputList[6]=8;
        inputList[7]=5;
        inputList[8]=4;
        inputList[9]=3;
        inputList[10]=2;
        
        outputList1[1]=2;
        outputList1[2]=3;
        outputList1[3]=6;
        outputList1[4]=5;
        outputList1[5]=4;
        outputList1[6]=10;
        outputList1[7]=8;
        outputList1[8]=11;
        outputList1[9]=7;
        outputList1[10]=9;
        
        outputList2[1]=5;
        outputList2[2]=7;
        outputList2[3]=6;
        outputList2[4]=11;
        outputList2[5]=9;
        outputList2[6]=10;
        outputList2[7]=8;
        
    end
    always #5 clk = ~clk;
  
    initial begin
        $display("Starting Testbench");
        $display("Check listBusy==0 when mode is checkIn");
        mode=2;//checkIn
        studentID=inputList[1]; //insert student 11
        checkInTime=inputList[1];
        #6 //6
        if (listBusy==0) begin result=result+1; $display("time:%2d",$time,",PASSED: listBusy==0."); end else $display("time:%2d",$time,",FAILED: In checkIn mode listBusy should be 0.");
        #1 //7   //insert students: 10,9,6,7,8,5,4,3,2
        for (i=2;i<=10;i=i+1)
        begin
            studentID=inputList[i];
            checkInTime=inputList[i];
            #10;
        end
        #1 //_8
        mode=0; //list
        $display("In list mode, check listBusy=1 and ready=0 while listing studentIDs");
        #10 //_8
        if (listBusy==1)  begin result=result+1; $display("time:%2d",$time,",PASSED: listBusy==1."); end else $display("time:%2d",$time,",FAILED: While listing studentIDs listBusy should be 1.");
        if (ready==0)  begin result=result+1; $display("time:%2d",$time,",PASSED: Ready==0."); end else $display("time:%2d",$time,",FAILED: While listing studentIDs ready should be 0.");
        $display("The heap contents that must be listed in the following order: 2,3,6,5,4,10,8,11,7,9");
        for (i=1;i<=10;i=i+1)
        begin
            if (listOutput==outputList1[i])  $display("time:%2d",$time,",PASSED: heap[%2d]==%2d.",i,outputList1[i]); 
            else
            begin
                $display("time:%2d",$time,",FAILED: The %2d. element in the heap should be %d , but your listOutput is %d.",i,outputList1[i],listOutput);
                minHeapOk=0;
            end
            #10; //_8
        end
        if (minHeapOk==1) result=result+10;
        $display("Finished checking heap contents.");
        $display("After listing finishes, check ready=1 and listBusy=0");
        if (listBusy==0)  begin result=result+1; $display("time:%2d",$time,",PASSED: listBusy==0."); end else $display("time:%2d",$time,",FAILED: After listing finished, listBusy should be 0.");
        if (ready==1)  begin result=result+1; $display("time:%2d",$time,",PASSED: Ready==1."); end else $display("time:%2d",$time,",FAILED: After listing finished, ready should be 1.");
        $display("Listing starts from the beginning: check ready=0, listBusy=1, listOutput=2");
        #10 //_8
        if (listBusy==1) begin result=result+1; $display("time:%2d",$time,",PASSED: listBusy==1."); end else $display("time:%2d",$time,",FAILED: While listing studentIDs listBusy should be 1.");
        if (ready==0) begin result=result+1; $display("time:%2d",$time,",PASSED: ready==0."); end else $display("time:%2d",$time,",FAILED: While listing studentIDs ready should be 0.");
        if (listOutput==outputList1[1]) begin result=result+1; $display("time:%2d",$time,",PASSED: listOutput==2."); end else $display("time:%2d",$time,",FAILED: Listing should start from the beginning. The first element in the list should be  %d.",outputList1[1]);
        $display("Check If pharmacy capacity is full then the student is not allowed to enter the pharmacy.");
        #1 //_9
        mode=2; //checkIn
        #1 //_0
        studentID=1;
        checkInTime=1;
        #6 //_6
        mode=0; //list
        #10 //_6
        if (listOutput==outputList1[1]) begin result=result+2; $display("time:%2d",$time,",PASSED: heap[%2d]==%2d.",1,outputList1[1]); end else $display("time:%2d",$time,",FAILED: If pharmacy capacity is full then the student should not be added to the pharmacy. The first elemant in the heap should be %d but you listed %2d.",outputList1[1],listOutput);
        //CASE: Check delete minimum mode
        mode2=2; //checkIn
        $display("inserting students 11,10,9,6,7,8,5,4,3,2");
        for(i=1;i<=10;i=i+1) 
        begin
            studentID2=inputList[i];
            checkInTime2=inputList[i];
            #10; //_6
        end
        #1 //_7
        $display("delete 3 times");
        mode2=3; // deleteMin mode
        #30 //_7:  delete 3 times
        #1 //_8
        mode2=0; //list
        $display("Heap contents must be listed in the following order: 5,7,6,11,9,10,8");
        for (i=1;i<=7;i=i+1) 
        begin
            #10; //_8
            if (listOutput2==outputList2[i]) begin $display("time:%2d",$time,",PASSED: heap[%2d]==%2d.",i,outputList2[i]); end 
            else 
            begin
                $display("time:%2d",$time,",FAILED: The %2d. element in the heap should be %d, but your listOutput is %d.",i,outputList2[i],listOutput2);
                deleteMinOk=0;
            end
        end
        if (deleteMinOk==1) result=result+10;
        
        #1
        $display("Result is:%d",result*2);
        $finish;
    end //end initial

endmodule
