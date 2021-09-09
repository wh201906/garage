import pyvisa

visa_dll = "C:/Windows/System32/visa32.dll"
deviceName = "DSA2522"

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

# device.write(':AUToset')

device.write(':WAV:BEG CH1')
device.write(':WAV:PRE?')
device.write(':WAV:RANG 0,10000')
device.write(':WAV:FETC?')
head = device.read_bytes(2)
headLen = head[1] - ord('0')
print(headLen)
len = device.read_bytes(headLen)
len = int(len)
print(len)
data = device.read_bytes(len)
device.write(':WAV:END')
print(data)

device.close()