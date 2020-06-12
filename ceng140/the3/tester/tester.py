import os
import time

NUM_OF_TESTCASE = 6
wrong = 0
wrong_tcs = []
bar = 30
t1 = time.time()

print(bar * '.',end = '')
print("0%",end = '\r')

for i in range(1,NUM_OF_TESTCASE+1):
	time.sleep(0.5)
	tc = "tc/testcase"+str(i)+".c"
	outp = "out/output"+str(i)+".txt"
	expe = "exp/expected"+str(i)+".txt"

	
	os.system("gcc -ansi -Wall -pedantic-errors the3.c tc/testcase"+str(i)+".c -lm -o a")

	os.system("./a  >"+outp)

	output = open(outp,"r+")
	out = output.read()

	expected = open(expe,"r+")
	exp = expected.read()

	if(exp != out):
		print( "Testcase"+str(i)+" Failed!\n")
		print("Correct Output:\n"+exp)
		print("\nYour Output:\n"+out)
		wrong_tcs.append("Testcase"+str(i))
		wrong+=1



	progress = int((i/NUM_OF_TESTCASE)*bar)
	percantage = round((progress*100)/bar,1)
	print(progress*'#',end='')
	print((30-progress)*'.',end = '')
	print(str(percantage)+ "%",end='\r')

print("\nYou failed " + str(wrong) + " times on "+str(NUM_OF_TESTCASE)+" testcases.")
print("You failed on the cases: {}".format(wrong_tcs))
t2 = time.time()
t2 -= 3
print("Execute time is: {}".format(t2-t1))
