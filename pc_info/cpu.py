import re
import os

file1 = open("cpuinfo_.txt", "r")
# file1 = open(os.getcwd()+"/pc_info/cpuinfo_.txt", "r")
arr=[]

for line in file1:
    arr2=line.split(":")
    for i in range(len(arr2)):
        arr2[i] = arr2[i].strip('\n').strip('\t')
    arr.append(arr2)

processors=0
model_name=''
total_cores=0
total_cache=0
cpu_MHz=0

for val in arr:
    if(val[0]=='processor'):
        processors+=1
    elif(val[0]=='model name'):
        model_name=val[1]
    elif(val[0]=='cpu cores'):
        total_cores=int(val[1])
    elif(val[0]=='cpu MHz'):
        cpu_MHz=float(val[1][1:])
    elif(val[0]=='cache size'):
        total_cache=int(val[1][:-2])
        
print()
print(f"Processors  : {processors}")
print(f"Model Name  :{model_name}")
print(f"Total Cores : {total_cores}")
print(f"Frequency   : {cpu_MHz} MHz")
print(f"CPU Cache   : {total_cache} Kb {str(round(total_cache/1048576, 2))} Gb")