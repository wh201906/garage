import pyvisa
from visadev import VisaDev
# USB interface requires other drivers


class FSC(VisaDev):
    def __init__(self, resource):
        super(FSC, self).__init__(resource)
        self.name = "FSC"

    def setCenterFreq(self, freq):
        self.write("FREQ:CENT " + str(freq) + "Hz")


if __name__ == '__main__':
    res = VisaDev.openProc()
    if res is None:
        exit(0)
    device = FSC(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    device.setCenterFreq(100000000)

    device.close()