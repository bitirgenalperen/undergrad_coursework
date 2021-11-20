# -*- coding: utf-8 -*-
"""
Created on Fri Nov 29 00:19:45 2019

@author: bitirgen.alperen
"""

def isCovered(al,ah,bl,bh,cl,ch):
 k= 'NOT COMPLETELY COVERED' # since there are specific cases to cover the mining area; if does not fit any if-else statement it means 'NOT COMPLETELY COVERED' 
 a = [al[0],ah[0],al[1],ah[1]]
 if (bl[0]+bh[0])<=(cl[0]+ch[0]):# to state the list b as the one with lower geometric center point                  
 				 # with respect to x-axis; which allows us to eliminate nested if-else statements in further steps  
     b = [bl[0],bh[0],bl[1],bh[1]]
     c = [cl[0],ch[0],cl[1],ch[1]]
 elif(bl[0]+bh[0])>(cl[0]+ch[0]):
     b = [cl[0],ch[0],cl[1],ch[1]]
     c = [bl[0],bh[0],bl[1],bh[1]]
     
     
 if(b[0]<=a[0]) and (b[1]>=a[1]) and (b[2]<=a[2])and(b[3]>=a[3]):k = 'COMPLETELY COVERED' #case where the lower geometric center pointed shape covers mining area
 elif(c[0]<=a[0]) and (c[1]>=a[1]) and (c[2]<=a[2])and(c[3]>=a[3]):k = 'COMPLETELY COVERED' #case where the higher geometric center pointed shape covers mining area
 elif(b[1]>=c[0]) and (c[1]>=a[1]) and (b[0]<=a[0]) and (b[2]<=a[2]) and (c[2]<=a[2])and (b[3]>=a[3]) and (c[3]>=a[3]):#case where the shapes collaborate to cover the ming area depending on x-axis positions
     k = 'COMPLETELY COVERED'
 elif (b[0]<=a[0])and (b[1]>=a[1])and(c[0]<=a[0])and (c[1]>=a[1]):#case where the shapes collaborate to cover the ming area depending on y-axis positions
     if(b[3]>=a[3])and(c[2]<=a[2])and (b[2]<=c[3]):k = 'COMPLETELY COVERED'
     elif(c[3]>=a[3])and(b[2]<=a[2])and (c[2]<=b[3]):k = 'COMPLETELY COVERED'
 return k
