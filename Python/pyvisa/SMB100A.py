import pyvisa
from visadev import VisaDev
from time import time


class SMB100A(VisaDev):
    def __init__(self, resource):
        super(SMB100A, self).__init__(resource)
        self.name = "SMB100A"

    def rf_getFreq(self):
        return float(device.query(':FREQ?'))

    # "*OPC" doesn't work as expected
    # "*OPC?" will work
    def rf_setFreq(self, freq=1000, waitFinished=True):
        device.write(':FREQ ' + str(freq))
        if waitFinished:
            return device.query("*OPC?")

    def rf_setFreq_check(self, freq=1000):
        self.rf_setFreq(freq)
        return self.rf_getFreq() == freq
    
    def rf_setOutput(self, state):
        device.write(":OUTP " + ("ON" if state else "OFF"))

    def rf_getOutput(self):
        result = device.query(":OUTP?").upper()
        if "ON" in result or "1" in result:
            result = True
        elif "OFF" in result or "0" in result:
            result = False
        else:
            result = None
        return result


if __name__ == '__main__':

    res = VisaDev.openProc(2, '169.254.2.20')
    if res is None:
        exit(0)
    device = SMB100A(res)

    if device.check() is False:
        print('Error: This device is not ' + device.getName() + '?')
        device.close()
        exit(0)
    else:
        print(device.getName() + " connected")

    print(device.rf_getOutput())
    print(device.rf_getFreq())
    device.rf_setFreq(300000000)
    device.rf_setOutput(False)
    device.close()