import pyvisa
from visadev import VisaDev
from time import time, sleep


class SDG2122X(VisaDev):
    def __init__(self, resource):
        super(SDG2122X, self).__init__(resource)
        self.name = "SDG2122X"

    def getParameters(self, ch=1):
        return self.query('C' + str(ch) + ':BSWV?')

    def setFreq(self, ch=1, freq=1000):
        self.write('C' + str(ch) + ':BSWV FRQ,' + str(freq))


if __name__ == '__main__':

    res = VisaDev.openProc(1, 'USB0::0xF4EC::0x1102::SDG2XCAX4R0459::INSTR')
    if res is None:
        exit(0)
    device = SDG2122X(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    t1 = time()
    for i in range(10, 20000, 10):
        device.setFreq(1, i)
        print(device.getParameters(1))

    t2 = time()
    print(t2 - t1)

    device.close()