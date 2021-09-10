import pyvisa
from visadev import VisaDev
from time import time


class DG822(VisaDev):
    def __init__(self, resource):
        super(DG822, self).__init__(resource)
        self.name = "DG822"

    def getFreq(self, ch=1):
        return float(device.query(':SOUR' + str(ch) + ':FREQ?'))

    # "*OPC" doesn't work as expected
    # "*OPC?" will work
    def setFreq(self, ch=1, freq=1000, waitFinished=True):
        device.write(':SOUR' + str(ch) + ':FREQ ' + str(freq))
        if waitFinished:
            return device.query("*OPC?")

    def setFreq_check(self, ch=1, freq=1000):
        self.setFreq(ch, freq)
        return self.getFreq(ch) == freq


if __name__ == '__main__':

    res = VisaDev.openProc(1, 'USB0::0x1AB1::0x0643::DG8A214803371::INSTR')
    if res is None:
        exit(0)
    device = DG822(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    t1 = time()
    for i in range(10, 30000, 10):
        device.setFreq(1, i)
        device.delay_ns(300000)
        # sleep is necessary there, otherwise the time can be much longer(4.7s->25s)
        # A FIFO might be in the communication path, if the FIFO is always full,
        # the PC or the DG822 might take extra instructions to handle this situration.

        # print(device.getFreq(1))
    t2 = time()
    print(t2 - t1)
    # device.write(':SOUR1:FUNC SIN')
    # device.write(':SOUR1:FREQ 500')
    # device.write(':SOUR1:VOLT 2.5')
    # device.write(':SOUR1:VOLT:OFFS 1')
    # device.write(':SOUR1:PHAS 90')
    # device.write(':OUTP1 ON')

    device.close()