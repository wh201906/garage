import pyvisa
from visadev import VisaDev


class MSOX3052A(VisaDev):
    def __init__(self, resource):
        super(MSOX3052A, self).__init__(resource)
        self.name = "3052A"


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

    device.write(':AUToscale')

    device.close()