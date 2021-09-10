import pyvisa
from visadev import VisaDev


class DSA2522(VisaDev):
    def __init__(self, resource):
        super(DSA2522, self).__init__(resource)
        self.name = "DSA2522"


if __name__ == '__main__':
    res = VisaDev.openProc()
    if res is None:
        exit(0)
    device = DSA2522(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    device.write(':AUToset')

    # Failed to read
    # device.write(':WAV:BEG CH1')
    # device.write(':WAV:PRE?')
    # device.write(':WAV:RANG 0,10000')
    # device.write(':WAV:FETC?')
    # head = device.read_bytes(2)
    # headLen = head[1] - ord('0')
    # print(headLen)
    # len = device.read_bytes(headLen)
    # len = int(len)
    # print(len)
    # data = device.read_bytes(len)
    # device.write(':WAV:END')
    # print(data)

    device.close()