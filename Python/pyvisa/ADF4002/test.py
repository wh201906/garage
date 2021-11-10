import sys, os
import serial
from time import sleep

ipath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
print(ipath)
sys.path.append(ipath)

from DSA815 import DSA815, VisaDev


def waitReady(port):
    buf = None
    while True:
        buf = port.read_all()
        if buf == b'':
            continue
        elif b'e' in buf:
            return 'err'
        elif b'o' in buf:
            return 'ok'
        elif b'p' in buf:
            return 'par'


def getDevice():
    res = VisaDev.openProc(1, 'USB0::0x1AB1::0x0960::DSA8A211000206::INSTR')
    if res is None:
        exit(0)
    device = DSA815(res)
    return device


def process(device, port, freq, times):
    device.setCenterFreq(freq)
    device.write("*WAI")

    val = freq / 20000
    port.write(bytes(str(val) + '\n', 'utf-8'))
    result = waitReady(port)
    if result == 'err':
        print("fully unlocked at:", freq)
    elif result == 'par':
        print("partially unlocked at:", freq)
    for i in range(times):
        device.write(":INIT")
        # sleep(1.5)
        device.write("*WAI")
        device.query("*OPC?")
        # print(device.trace_get())
        # print(i + 1)


try:
    port = serial.Serial("COM10", 115200)
    device = getDevice()
    device.timeout = 5000
    device.write(":INIT:CONT 0")  # single mode

    for freq in range(int(87e6), int(109e6 + 20000), int(1e5)):
        process(device, port, freq, 1)

    port.close()
    device.close()
except Exception as e:
    print(e)