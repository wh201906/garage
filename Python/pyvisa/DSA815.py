import pyvisa
from visadev import VisaDev
from struct import unpack


class DSA815(VisaDev):
    def __init__(self, resource):
        super(DSA815, self).__init__(resource)
        self.name = "DSA815"

    def setCenterFreq(self, freq):
        self.write(":FREQ:CENT " + str(freq))

    def trace_get(self):
        byteorder = device.query(":FORM:BORD?").lower()
        if "norm" in byteorder:
            byteorder = "<"
        else:
            byteorder = ">"
        device.write(":FORM REAL")
        device.write(":TRAC? TRACE1")
        len = device.read_bytes(11)
        len = int(len[-9:])
        data = device.read_bytes(len)
        fmt = byteorder + "f" * (len // 4)
        return unpack(fmt, data)


if __name__ == '__main__':
    res = VisaDev.openProc(1)
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
    print(device.trace_get())

    device.close()