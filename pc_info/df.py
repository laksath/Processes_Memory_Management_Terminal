import os

def round_eval(x):
    if(round(x/1048576, 2)<10):
        return " "+str(round(x/1048576, 2))
    return str(round(x/1048576, 2))

file1 = open("df.txt", "r")
# file1 = open(os.getcwd()+"/pc_info/df.txt", "r")
arr=[]
for line in file1:
    arr.append(line.split())

tot_mem=0
tot_tmpfs=0
tot_used=0
tot_free=0

for val in arr:
    try:
        tot_mem+=int(val[1])
        tot_used+=int(val[2])
        tot_free+=int(val[3])
    except:
        continue
    if val[0]=="tmpfs":
        tot_tmpfs+=int(val[1])
    

print()
print(f"Total Space Allocated : {round_eval(tot_mem)} Gb {tot_mem} Kb")
print(f"Total tmpfs Allocated : {round_eval(tot_tmpfs)} Gb  {tot_tmpfs} Kb")
print(f"Total used  Space     : {round_eval(tot_used)} Gb {tot_used} Kb")
print(f"Total free  Space     : {round_eval(tot_free)}  Gb {tot_free} Kb")
print()
print(f"{str(round(tot_used*100/tot_mem,2))} % Space Occupied")
print(f"{str(round(100 - tot_used*100/tot_mem,2))} % Free space Available")
print()