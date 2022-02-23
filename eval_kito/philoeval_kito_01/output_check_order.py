
from ast import Sub
from socketserver import ThreadingUnixDatagramServer

fd = open("output", "r")
text = fd.readlines()


num_lines = sum(1 for line in open('output'))

#print(num_lines)
#print(text)


## GET EVERY FIRST ELEMENT OF EACH STRING IN ARRAY

i = 0
while (i < num_lines - 10):
	a = int(text[i].split(' ', 1)[0])
	b = int(text[i + 1].split(' ', 1)[0])

	if (b < a):
		print("       Error: time-order in line", i + 2)
		print("a,", a, "b", b)
		exit (1)
	i += 1
exit (0)
