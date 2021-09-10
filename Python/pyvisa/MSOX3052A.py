import pyvisa
from visadev import VisaDev
from time import time, sleep


class MSOX3052A(VisaDev):
    def __init__(self, resource):
        super(MSOX3052A, self).__init__(resource)
        self.name = "3052A"

    def gen_getFreq(self):
        return float(device.query(":WGEN:FREQuency?"))

    def gen_setFreq(self, freq, waitFinished=True):
        device.write(":WGEN:FREQuency " + str(freq))
        if waitFinished:
            return device.query("*OPC?")

    def measure_Vpp(self, ch=1):
        device.write(":MEASure:VPP CHANnel" + str(ch))
        return float(device.query(":MEASure:VPP?"))


if __name__ == '__main__':
    res = VisaDev.openProc(1, 'USB0::0x0957::0x17A3::MY51350010::INSTR')
    if res is None:
        exit(0)
    device = MSOX3052A(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    # device.write(':AUToscale')
    print(device.gen_getFreq())

    t1 = time()
    #~50ms per cycle
    for i in range(10700000, 10900000, 1000):
        device.gen_setFreq(i)
        print(device.measure_Vpp(1))
        # print(device.gen_getFreq())
    t2 = time()
    print(t2 - t1)

    device.close()