import pyvisa
from visadev import VisaDev


class DS2202A(VisaDev):
    def __init__(self, resource):
        super(DS2202A, self).__init__(resource)
        self.name = "2202A"
        self.inst.timeout += 2000

    def wave_getScreenData(self, ch):
        self.write(":WAV:SOUR CHAN" + str(ch))
        self.write(":WAV:MODE NORM")
        self.write(":WAV:FORM BYTE")
        self.write(":WAV:RES")
        self.write(":WAV:BEG")
        self.write(":WAV:DATA?")
        dataLen = self.read_bytes(11)
        dataLen = int(dataLen[-9:])
        return self.read_bytes(dataLen)

    def ch_setScale(self, ch, scale):
        self.write(":CHAN" + str(ch) + ":SCAL " + str(scale))

    def time_setScale(self, scale):
        self.write(":TIM:SCAL " + str(scale))

    def measure_Vpp(self):
        return float(self.query(":MEAS:VPP? CHAN1"))
    
    def measure_freq(self):
        return float(self.query(":MEAS:FREQ? CHAN1"))

    def measure_freqHW(self):
        return float(self.query(":MEAS:COUN:VAL?"))

    def display_getScreen(self):
        self.write(":DISP:DATA?")
        length = self.read_bytes(11)
        length = int(length[-9:])
        data = self.read_bytes(length)
        return data


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