from math import *

for i in range(300):
    val = sin(i / 300.0 * 2 * pi) * 2000 + 2000
    print(int(val),end=",")