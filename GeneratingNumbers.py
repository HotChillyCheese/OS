import random as rd
f = open("input.txt","w+")
for i in range(10000):
    f.write(str(rd.randint(1,5000)))
    f.write(" ")
f.close()