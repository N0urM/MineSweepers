#!/usr/bin/env python3
# Copyright 2009-2017 BHG http://bw.org/
import sys

sys.stdout = open('output.txt','wt')
alpha = '0ABCDEFGHIJKLMNOPQRS'
maparr = {}
 
 
for i in range (1 , 20) :

    for j in  range (1 , 20) :
       
        maparr[alpha[j] + str (i)] = 'Clear'
   
   # print (maparr[alpha[j] + str (i)] + " at " + alpha[j] + str (i) + '\n')    
             
while True :
    x = int (input ())
    y =  input ()
    s = input ()
    if s == 's' :
         maparr[alpha[x] + y ] = 'Surface Mine'
    elif s == 'b' :
        maparr[alpha[x] + y ] = 'Buried Mine'
    elif s == 'x' :
        break
    
print ("Surface mines detected at : " )

for i in range (1 , 20) :
    for j in  range (1 , 20) :
         if   maparr[alpha[j] + str (i)] == 'Surface Mine' :
            print ( alpha[j] + " " + str (i))
            

print ("Buried mines detected at : ")

for i in range (1 , 20) :
    for j in  range (1 , 20) :
         if   maparr[alpha[j] + str (i)] == 'Buried Mine' :
            print ( alpha[j] + " " + str (i))
            
            
            
            
