import pyvisa
from visadev import VisaDev


class DS2202A(VisaDev):
    def __init__(self, resource):
        super(DS2202A, self).__init__(resource)
        self.name = "2202A"
        self.inst.timeout += 2000

    def wave_getScreenData(self, ch):
        device.write(":WAV:SOUR CHAN" + str(ch))
        device.write(":WAV:MODE NORM")
        device.write(":WAV:FORM BYTE")
        device.write(":WAV:RES")
        device.write(":WAV:BEG")
        device.write(":WAV:DATA?")
        len = device.read_bytes(11)
        len = int(len[-9:])
        return device.read_bytes(len)

    def ch_setScale(self, ch, scale):
        device.write(":CHAN" + str(ch) + ":SCAL " + str(scale))

    def time_setScale(self, scale):
        device.write(":TIM:SCAL " + str(scale))


if __name__ == '__main__':
    res = VisaDev.openProc(1, 'USB0::0x1AB1::0x04B0::DS2G162350046::INSTR')
    if res is None:
        exit(0)
    device = DS2202A(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    # device.write(':AUToscale')
    print(device.wave_getScreenData(1))
    print(device.query(":WAV:PRE?"))
    device.ch_setScale(1, 0.0005)
    device.time_setScale(0.002)
    device.close()