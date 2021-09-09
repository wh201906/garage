import pyvisa
from time import sleep
from visadev import VisaDev

class NDS202(VisaDev):

    def __init__(self, resource):
        super(NDS202,self).__init__(resource)
        self.inst.write_termination = '\n'
        self.inst.read_termination = '\n'
        self.inst.timeout = 4000
        self.name = "NDS202"

    def queryWithLen(self, cmd):
        self.inst.write(cmd)
        len = int.from_bytes(self.inst.read_bytes(4), byteorder='little')
        data = self.inst.read_bytes(len)
        return data

# device.query(): first 4 bytes indicates the length of the result
# device.inst.query(): pyvisa.Resource.query()

visa_dll = "C:/Windows/System32/visa32.dll"

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
device = NDS202(device)

if device.check() is False:
    print('Error: This device is not ' + device.getName() + '?')
    device.close()
    exit()

# device.write(":AUTOset ON")

print(device.queryWithLen(":DATA:WAVE:SCREen:HEAD?"))

data = device.queryWithLen(":DATA:WAVE:SCREen:CH1?")
lis = []
for i in range(0, len(data), 2):
    lis.append(int.from_bytes(data[i:i + 2], byteorder='little', signed=True))
print(lis)

print(device.query(":MEASUrement:CH1:PKPK?"))

device.write(":CHANnel CH1")
print(device.query(":FUNCtion?"))
print(device.query(":FUNCtion:FREQuency?"))

device.write(":CHANnel CH2")
print(device.query(":FUNCtion?"))
print(device.query(":FUNCtion:FREQuency?"))
device.write(":FUNCtion:FREQuency 50000")
device.write(":FUNCtion SQUare")

device.close()