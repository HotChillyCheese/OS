filenames = []
for i in range(1,46):
    filenames.append("/Users/bohdan_pikula/Desktop/Lab3/Virtual Disk/1 folder/2 folder/3 folder/4 folder/5 folder/6 folder/7 folder/8 folder/9 folder/"+str(i)+"_process.txt")
with open("/Users/bohdan_pikula/Desktop/Lab3/Virtual Disk/1 folder/processes.txt", 'w') as outfile:
    for fname in filenames:
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)
    
filenames1 = []
for i in range(0,46):
    filenames1.append("/Users/bohdan_pikula/Desktop/Lab3/Virtual Disk/1 folder/2 folder/3 folder/4 folder/5 folder/6 folder/7 folder/8 folder/9 folder/10 folder/11 folder/"+str(i)+"_thread.txt")
with open("/Users/bohdan_pikula/Desktop/Lab3/Virtual Disk/1 folder/2 folder/3 folder/4 folder/threads.txt", 'w') as outfile:
    for fname in filenames1:
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)
