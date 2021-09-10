import pyvisa
from visadev import VisaDev


class DSA815(VisaDev):
    def __init__(self, resource):
        super(DSA815, self).__init__(resource)
        self.name = "DSA815"

    def setCenterFreq(self, freq):
        self.write(":FREQ:CENT " + str(freq))


if __name__ == '__main__':
    res = VisaDev.openProc()
    if res is None:
        exit(0)
    device = DSA815(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    device.setCenterFreq(1000000)

    device.close()