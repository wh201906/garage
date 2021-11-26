from SDG2122X import SDG2122X
from DS2202A import DS2202A, VisaDev
import sys
from time import sleep
import matplotlib.pyplot as plt

gen = VisaDev.openProc(1, 'USB0::0xF4EC::0x1102::SDG2XCAX4R0459::INSTR')
if gen is None:
    print("Generator not connected")
    sys.exit(0)
gen = SDG2122X(gen)
print(gen.query("*IDN?"))

oscillo = VisaDev.openProc(1, 'USB0::0x1AB1::0x04B0::DS2D234302864::INSTR')
if oscillo is None:
    print("Oscilloscope not connected")
    sys.exit(0)
oscillo = DS2202A(oscillo)
print(oscillo.query("*IDN?"))

# Vpp_out = float(input("Output voltage(V):\n"))
# start = int(input("Start freqency(Hz):\n"))
# stop = int(input("Stop frequency(Hz):\n"))
# step = int(input("Frequency step(Hz):\n"))
Vpp_out = 1.0
start = 1000
stop = 90000
step = 1000

oscillo.write(":MEAS:SOUR CHAN1")
oscillo.write(":MEAS:COUN:SOUR CHAN1")

result = {}
gen.setFreq(start)
gen.query("*OPC?")
sleep(1)

for freq in range(start, stop + 1, step):
    gen.setFreq(1, freq)
    gen.query("*OPC?")
    sleep(0.3)
    realFreq = oscillo.measure_freqHW()
    vpp = oscillo.measure_Vpp()
    result[freq] = vpp
    print("freq:", freq, "freq_m:", realFreq, "Vpp:", vpp)

print(result)

xList = list(result.keys())
yList = list(result.values())
plt.plot(xList, yList)
plt.show()

