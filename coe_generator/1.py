from math import *
from matplotlib import pyplot as plt # for graphic preview

# FILENAME = "512_square.coe" # square wave
# FILENAME = "512_sine.coe" # sine wave
# FILENAME = "512_ramp.coe" # ramp wave
FILENAME = "512_triangle.coe"  # triangle wave
WIDTH = 8
DEPTH = 512

hex_table = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
points = []
out = []

file = open("E:/" + FILENAME, "w+")
file.write("memory_initialization_radix=16;\n")
file.write("memory_initialization_vector=")
base = 2**(WIDTH - 1) - 1
for i in range(DEPTH):
    # var = int(base + (-1 if i >= DEPTH // 2 else 1) * base) # square wave
    # var = int(base + sin(i / DEPTH * 2 * pi) * base) # sine wave
    # var = int(i / DEPTH * (2 ** WIDTH - 1)) # ramp wave
    var = int((1 - abs((i * 2 / (DEPTH - 1)) - 1)) * (2**WIDTH - 1))  # triangle wave
    if var >= 2**WIDTH:
        var = 2**WIDTH - 1
    points.append(var)
    var_hex = ""
    while (var > 0):
        var_hex += hex_table[var & 0xf]
        var >>= 4
    var_hex += '0' * ((WIDTH - 1) // 4 - len(var_hex) + 1)
    out.append(var_hex[::-1])
for i in range(DEPTH):  # reverse
    print(out[DEPTH - i - 1], end=" ")
    file.write(out[DEPTH - i - 1] + " ")
file.close()
plt.plot(points) # for graphic preview
plt.show() # for graphic preview
