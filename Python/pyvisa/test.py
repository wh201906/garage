import pyvisa
from visadev import VisaDev

visa_dll = "C:/Windows/System32/visa32.dll"

device = VisaDev.openProc()

info = device.query("*IDN?")
print(info)

device.close()