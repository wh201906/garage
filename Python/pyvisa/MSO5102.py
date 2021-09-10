import pyvisa
from visadev import VisaDev


class MSO5102(VisaDev):
    def __init__(self, resource):
        super(MSO5102, self).__init__(resource)
        self.name = "MSO5102"
        self.inst.timeout += 2000


if __name__ == '__main__':
    res = VisaDev.openProc()
    if res is None:
        exit(0)
    device = MSO5102(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    device.write(':AUToscale')

    device.close()