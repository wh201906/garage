import pyvisa
from visadev import VisaDev


class DS2202A(VisaDev):
    def __init__(self, resource):
        super(DS2202A, self).__init__(resource)
        self.name = "2202A"
        self.inst.timeout += 2000


if __name__ == '__main__':
    res = VisaDev.openProc()
    if res is None:
        exit(0)
    device = DS2202A(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    device.write(':AUToscale')

    device.close()