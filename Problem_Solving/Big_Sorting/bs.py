#!/usr/bin/python

import sys
import timeit

start = timeit.timeit()
with open(sys.argv[1], 'r') as in_file:
    n = int(in_file.readline())
    unsorted = []
    for i in range(n):
        unsorted.append(in_file.readline().strip())
end = timeit.timeit()
print("Time it took to read input: " + str(end - start))

start = timeit.timeit()
unsorted.sort()
unsorted.sort(key = len)
#that would work for integers shorter than 4300 digits
#unsorted.sort(key=int)
end = timeit.timeit()
print("Time it took to sort: " + str(end - start))
print('\n')
for i in range(n):
    print(unsorted[i])
