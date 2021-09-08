import pyvisa

visa_dll = "C:/Windows/System32/visa32.dll"
deviceName = "NDS202"

rm = pyvisa.ResourceManager(visa_dll)
cmd = ""
while cmd == "" or cmd == "r" or cmd == "refresh":
    ip = input("Connect to(IP):")
    cmd = ip.lower()
if (cmd == 'q' or cmd == 'e' or cmd == 'quit' or cmd == 'exit'):
    print("Exited")
    exit()
cmd = ""
while cmd == "" or cmd == "r" or cmd == "refresh":
    port = input("Connect to(Port):")
    cmd = port.lower()
if (cmd == 'q' or cmd == 'e' or cmd == 'quit' or cmd == 'exit'):
    print("Exited")
    exit()

device = rm.open_resource("TCPIP::" + ip + "::" + port + "::SOCKET")
device.write_termination = '\n'
device.read_termination = '\n'

info = device.query("*IDN?")
print(info)

if info.find(deviceName) == -1:
    print('Error: This device is not ' + deviceName + '?')
    device.close()
    exit()

device.write(":AUTOset ON")

device.close()