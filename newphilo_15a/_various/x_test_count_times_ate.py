

fd = open("outfile", "r")
text = fd.readlines()

## finds 2nd word in text
# for j in text:
# 	print(j.split(' ', 2)[1])


## find nr of philos #########################################
largest = 1
for j in text:
	if largest < int(j.split(' ', 2)[1]):
		largest = int(j.split(' ', 2)[1])
		#print(largest)
#largest = 5
print("Nr philosophers: ", largest)


## make both arrays ##########################################
arr_filos_id = [x for x in range(1, largest + 1)]
arr_times_ate = [0] * (largest + 1)


# for j in text:
# 	#print(j)
# 	print(int(j.split(' ', 5)[0]))

#print("text j", text[0])
# print("text[0]", text[0].split(' ', 3)[3])


## count first value in each line ############################
i = 0
for j in text:
	if (text[i].split(' ', 3)[3] == "eating\n"):
		arr_times_ate[int(j.split(' ', 2)[1])] += 1
		#print("ONLY", j.split(' ', 2)[1], arr_times_ate[int(j.split(' ', 2)[1])])
	i += 1


## print Philosofer's id's ###################################
i = 0
print("  Philosofer ID", end="")
while i < largest:
	print("{0:4d}".format(arr_filos_id[i]), end="")
	i += 1
print("")




# ## print result: times ate ###################################
i = 1
print("  Ate times    ", end="")
while i <= largest:
	#if (text[i].split(' ', 3)[3] == "eating\n"):
	print("{0:4d}".format(arr_times_ate[i]), end="")
	i += 1
print("\n")
