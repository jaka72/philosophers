
from ast import Sub
from socketserver import ThreadingUnixDatagramServer

fd = open("output", "r")
text = fd.readlines()


## COUNT LINES WITH "eating" ########################
nrlines = 0
for j in text:
	if (  (j.split(' ', 1)[0]).isdigit()):
				
		if (int(j.split(' ', 1)[0]) < 20):
			if (j.split(' ', 4)[3] == "eating"):
				nrlines += 1
	#print(j[1])  # these are each chars[]
print(nrlines)



## MAKE ARRAY #############################################
orderarr = [0] * (nrlines)



## SAVE "eating" VALUES INTO ARRAY #################### 
i = 0
for j in text:
	if (  (j.split(' ', 1)[0]).isdigit()):

		if (int(j.split(' ', 1)[0]) < 20):
			if (j.split(' ', 4)[3] == "eating"):
				orderarr[i] = int(j.split(' ', 2)[1])
				i += 1



## SORT ARRAY #############################################
orderarr.sort()
print(orderarr)



## CHECK IF ANY NUMBER MISSING #########################################
i = 0
x = orderarr[0]
while (i < nrlines):
	if (x != orderarr[i]):
		print("Missing:", orderarr[i])
		x += 2
	x += 2
	i += 1