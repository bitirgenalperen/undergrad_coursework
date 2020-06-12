import sys

def rule_check(r,n):
    if r[:-1]=='==':
        return n==int(r[-1])
    elif r[:-1]=='<':
        return n<int(r[-1])
    elif r[:-1]=='>':
    	return n>int(r[-1])
    	   

def cer(k):
  k = ['-'*len(k[0])]+k+['-'*len(k[0])]
  for i in range(len(k)):
    k[i]='-'+str(k[i])+'-'
  return k 
 
 
def frag_count(t):
  row = len(t)-2
  col = len(t[0])-2
  count_object = []
  for i in range(1,row+1):
    count_object.insert(i-1,[])
    for j in range(1,col+1):
      c = 0
      for z in range(-1,2):
        if t[i-1][j+z]=='*':
          c+=1
        if t[i+1][j+z]=='*':
          c+=1
        if t[i][j+z]=='*' and z!=0:
          c+=1
 
      count_object[i-1].append(c)
  return count_object   



rules,maps,gen,rule_p=[],[],0,[]

map_loc = sys.argv[1]
rule_loc = sys.argv[2]
rep = int(sys.argv[3])


lines = [line.rstrip('\n') for line in open(rule_loc)]
for t in lines:
  if t[1]=='=':
    rule_p.append(t[:2]+'='+t[2:])
  else:
    rule_p.append(t)		


maphandle = open(map_loc, "r")
for line in maphandle:
    if '\n' in line:
    	maps.append(line[:-1])
    else:
    	maps.append(line)

for gen in range(rep):
	map_n=[]
	maps2=cer(maps)
	map_c = frag_count(maps2)
	for row in range(1,len(maps2)-1):
		map_n.append('')
		for col in range(1,len(maps2[0])-1):
			map_n[-1] += maps[row-1][col-1]
			for rule in rule_p:
				if rule[0]==maps2[row][col] and rule_check(rule[1:-1],map_c[row-1][col-1]):
					map_n[-1]=  map_n[-1][:-1] + rule[-1]
	maps=map_n[:]


for tr in range(len(maps)):
	print maps[tr]	

	
	#COPY YOUR SOLUTION HERE#