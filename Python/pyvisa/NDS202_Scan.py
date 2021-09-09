from NDS202 import NDS202
from time import sleep

device = NDS202.openProc(NDS202.CONNECTTYPE_SOCKET, "192.168.3.72", 3000)
if device is None:
    exit(0)
device = NDS202(device)

if device.check() is False:
    print('Error: This device is not ' + device.getName() + '?')
    device.close()
    exit(0)
else:
    print(device.getName() + " connected")

result = {}

device.gen_setCurrCH(1)
device.gen_setAmp(1.5)
sleep(2) # necessary

# around 1.15s per cycle, pretty slow
for freq in range(10600000, 11000000, 10000):
    device.gen_setCurrFreq(freq) # around 52ms
    freq = device.gen_getCurrFreq() # around 0.4~0.6s
    print(freq)
    result[freq] = device.measure_Vpp() # around 0.5s

print(result)