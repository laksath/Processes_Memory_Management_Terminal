import os
import plotext as plt
import sys

os.chdir(sys.argv[1])

list_of_ls = os.popen("ls -l -S").read().split('\n')
dirs = os.popen("ls -d -S */").read().split('\n')

# print(list_of_ls)
# print(dirs)

list_of_ls=list_of_ls[1:-1]
readability=[]
month=[]
day=[]
time=[]
size=[]
dir_and_fnames=[]

for val in list_of_ls:
    data  = val.split()
    # print(val)
    # print(data)
    # print()
    dir_and_fnames.append(' '.join(data[8:]))
    time.append(data[7])
    day.append(data[6])
    month.append(data[5])
    size.append(data[4])

# print(sys.argv[1])
# print(readability)
# print(month)
# print(len(month))
# print(day)
# print(len(day))
# print(time)
# print(len(time))
# print(size)
# print(len(size))
# print(dir_and_fnames)
# print(len(dir_and_fnames))



size=[int(x) for x in size]

tot_size=sum(size)

files_and_directories = dir_and_fnames
percentages = [100*x/tot_size for x in size]
print()
print()
# plt.plot_size(100,20)
plt.frame(True)
plt.grid(True)
plt.bar([str(i) for i in range(1,len(files_and_directories)+1)], percentages)
plt.title("All Files + Directories Variation")
plt.show()

for x in range(len(dir_and_fnames)):
    print(f"{x+1}->{dir_and_fnames[x]}")
print()

for val in range(len(percentages)):
    print(f"{val+1} {dir_and_fnames[val]} -> {round(percentages[val],2)}%.\nMost recently used at : {time[val]} on {day[val]} {month[val]}.\n")