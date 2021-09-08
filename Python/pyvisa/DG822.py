import pyvisa

visa_dll = "C:/Windows/System32/visa32.dll"
deviceName = "DG822"

rm = pyvisa.ResourceManager(visa_dll)
cmd = ""
while cmd == "" or cmd == "r" or cmd == "refresh":
    print("Connected Devices:")
    print(rm.list_resources())
    port = input("Connect to:")
    cmd = port.lower()
if (cmd == 'q' or cmd == 'e' or cmd == 'quit' or cmd == 'exit'):
    print("Exited")
    exit()
device = rm.open_resource(port)

info = device.query("*IDN?")
print(info)

if info.find(deviceName) == -1:
    print('Error: This device is not ' + deviceName + '?')
    device.close()
    exit()

device.write(':SOUR1:FUNC SIN')
device.write(':SOUR1:FREQ 500')
device.write(':SOUR1:VOLT 2.5')
device.write(':SOUR1:VOLT:OFFS 1')
device.write(':SOUR1:PHAS 90')
device.write(':OUTP1 ON')

device.close()