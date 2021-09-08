import pyvisa
# USB interface requires other drivers

visa_dll = "C:/Windows/System32/visa32.dll"
deviceName = "FSC"

rm = pyvisa.ResourceManager(visa_dll)
cmd = ""
while cmd == "" or cmd == "r" or cmd == "refresh":
    ip = input("Connect to(IP):")
    cmd = ip.lower()
if (cmd == 'q' or cmd == 'e' or cmd == 'quit' or cmd == 'exit'):
    print("Exited")
    exit()

device = rm.open_resource("TCPIP::" + ip)

info = device.query("*IDN?")
print(info)

if info.find(deviceName) == -1:
    print('Error: This device is not ' + deviceName + '?')
    device.close()
    exit()

device.write("FREQ:CENT 100MHz")

device.close()