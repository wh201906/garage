import pyvisa
from visadev import VisaDev


class NDS202(VisaDev):
    def __init__(self, resource):
        super(NDS202, self).__init__(resource)
        self.inst.write_termination = '\n'
        self.inst.read_termination = '\n'
        self.name = "NDS202"

    # device.queryWithLen(): first 4 bytes indicates the length of the result
    # device.query(): pyvisa.Resource.query()

    def queryWithLen(self, cmd):
        self.inst.write(cmd)
        len = int.from_bytes(self.inst.read_bytes(4), byteorder='little')
        data = self.inst.read_bytes(len)
        return data

    def _measure_trim(self, str):
        str = str[str.index(":") + 2:-2]
        str = str.rstrip("?") # Vpp : 204.0mV?-> or Vpp : 204.0mV->
        return str

    def measure_Vmax(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":MAX?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def measure_Vmin(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":MIN?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def measure_Vpp(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":PKPK?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def measure_Vtop(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":VTOP?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def measure_Vbase(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":VBASe?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def measure_Vamp(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":VAMP?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def measure_Vave(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":AVERage?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val


# failed to read
# def measure_Vrms(self, ch=1):  # ch: 1 or 2, result in Volt
#     result = self.query(":MEASUrement:CH" + str(ch) + ":SQUAresum?")
#     result = self._measure_trim(result)
#     print(result)

    def measure_Vcyclerms(self, ch=1):  # ch: 1 or 2, result in Volt
        result = self.query(":MEASUrement:CH" + str(ch) + ":CYCRms?")
        result = self._measure_trim(result)
        if result[-2] == 'm':  # mV
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def measure_Freq(self, ch=1):  # ch: 1 or 2, result in Hz
        result = self.query(":MEASUrement:CH" + str(ch) + ":FREQuency?")
        result = self._measure_trim(result)
        if result[-3] == 'M':  # MHz
            val = float(result[:-3]) / 0.000001
        elif result[-3] == 'k' or result[-3] == 'K':  # kHz
            val = float(result[:-3]) / 0.001
        else:
            val = float(result[:-2])
        return val

    def measure_Period(self, ch=1):  # ch: 1 or 2, result in s
        result = self.query(":MEASUrement:CH" + str(ch) + ":PERiod?")
        result = self._measure_trim(result)
        if result[-2] == 'p':  # ps
            val = float(result[:-2]) * 0.000000000001
        elif result[-2] == 'n':  # ns
            val = float(result[:-2]) * 0.000000001
        elif result[-2] == 'u':  # us
            val = float(result[:-2]) * 0.000001
        elif result[-2] == 'm':  # ms
            val = float(result[:-2]) * 0.001
        else:
            val = float(result[:-1])
        return val

    def gen_setCurrCH(self, ch=1):  # ch: 1 or 2
        self.write(":CHANnel CH" + str(ch))

    def gen_setCurrFreq(self, freq=1000):  # ch: 1 or 2, freq in Hz
        self.write(":FUNCtion:FREQuency " + str(freq))

    def gen_getCurrFreq(self):
        return float(self.query(":FUNCtion:FREQuency?")[:-2])

    def gen_setFreq(self, ch=1, freq=1000):
        self.gen_setCurrCH(ch)
        self.gen_setCurrFreq(freq)

    def gen_enableCH(self, ch=1):
        self.write(":CHANnel:CH" + str(ch) + " ON")

    def gen_disableCH(self, ch=1):
        self.write(":CHANnel:CH" + str(ch) + " OFF")

    def gen_setCurrAmp(self, amp=1.5):  # ch: 1 or 2, amplitude in V
        self.write(":FUNCtion:AMPLitude " + str(amp))

    def gen_setAmp(self, ch=1, amp=1.5):
        self.gen_setCurrCH(ch)
        self.gen_setCurrAmp(amp)

    def gen_setCurrOffset(self, offset=1.5):  # ch: 1 or 2, offset in V
        self.write(":FUNCtion:OFFSet " + str(offset))

    def gen_setOffset(self, ch=1, offset=1.5):
        self.gen_setCurrCH(ch)
        self.gen_setCurrOffset(offset)

    def gen_setCurrHLevel(self, level=1.5):  # ch: 1 or 2, highlevel in V
        self.write(":FUNCtion:HIGH " + str(level))

    def gen_setHLevel(self, ch=1, level=1.5):
        self.gen_setCurrCH(ch)
        self.gen_setCurrHLevel(level)

    def gen_setCurrLLevel(self, level=1.5):  # ch: 1 or 2, lowlevel in V
        self.write(":FUNCtion:LOW " + str(level))

    def gen_setLLevel(self, ch=1, level=1.5):
        self.gen_setCurrCH(ch)
        self.gen_setCurrLLevel(level)

if __name__ == '__main__':

    res = VisaDev.openProc()
    if res is None:
        exit(0)
    device = NDS202(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    # device.write(":AUTOset ON")

    print(device.queryWithLen(":DATA:WAVE:SCREen:HEAD?"))

    data = device.queryWithLen(":DATA:WAVE:SCREen:CH1?")
    lis = []
    for i in range(0, len(data), 2):
        lis.append(
            int.from_bytes(data[i:i + 2], byteorder='little', signed=True))
    print(lis)

    print(device.measure_Vmax(1))
    print(device.measure_Vmin(1))
    print(device.measure_Vpp(1))
    print(device.measure_Vtop(1))
    print(device.measure_Vbase(1))
    print(device.measure_Vamp(1))
    print(device.measure_Vave(1))
    # print(device.measure_Vrms(1))
    print(device.measure_Vcyclerms(1))
    print(device.measure_Freq(1))
    print(device.measure_Period(1))

    device.write(":CHANnel CH1")
    print(device.query(":FUNCtion?"))
    print(device.query(":FUNCtion:FREQuency?"))

    device.gen_setFreq(2, 123456)

    device.close()