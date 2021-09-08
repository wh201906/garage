import pyvisa

visa_dll = "C:/Windows/System32/visa32.dll"
deviceName = "SDG2122X"

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

device.write('C1:BSWV WVTP,RAMP')
device.write('C1:BSWV FRQ,2000')
device.write('C1:BSWV AMP,3')

device.close()