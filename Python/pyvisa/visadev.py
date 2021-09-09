import pyvisa

class VisaDev():

    def __init__(self, resource):
        self.inst = resource
        self.name = ""

    # exposed
    def query(self, cmd):
        return self.inst.query(cmd)

    def write(self, cmd):
        return self.inst.write(cmd)

    def close(self):
        return self.inst.close()

    # other functions
    def info(self):
        return self.inst.query("*IDN?")

    def check(self):
        return (self.info().find(self.name) != -1)

    def getName(self):
        return self.name

    def readAll(self): # read until timeout
        data = bytearray()
        while True:
            try:
                data += self.inst.read_bytes(1)
            except pyvisa.errors.VisaIOError: # usually cause by timeout
                break
        return data

    # for interaction
    @staticmethod
    def inputProc(text):
        userInput = ""
        userInput_Lower = ""
        while userInput_Lower == "" or userInput_Lower == "r" or userInput_Lower == "refresh":
            userInput = input(text)
            userInput_Lower = userInput.lower()
        if (userInput_Lower == 'q' or userInput_Lower == 'e' or userInput_Lower == 'quit' or userInput_Lower == 'exit'):
            return None
        else:
            return userInput

    CONNECTTYPE_USB = 1
    CONNECTTYPE_ETHERNET = 2
    CONNECTTYPE_SOCKET = 3

    @staticmethod
    def openProc(type=0, addr=None, port=None):
        visa_dll = "C:/Windows/System32/visa32.dll"

        rm = pyvisa.ResourceManager(visa_dll)

        while int(type) not in range(1,4):
            type = VisaDev.inputProc("Connection type(1:USB 2:Ethernet 3:SOCKET):\n")
            if type is None:
                return None
        type = int(type)

        if addr is None:
            if type == VisaDev.CONNECTTYPE_USB:
                print("Available devices:")
                print(rm.list_resources())
                addr = VisaDev.inputProc("Connect to:\n")
            else:
                addr = VisaDev.inputProc("Connect to(IP address):\n")
            if addr is None:
                return None

            if type == VisaDev.CONNECTTYPE_SOCKET and port is None:
                port = VisaDev.inputProc("Connect to(port):\n")
                if port is None:
                    return None

        if type == VisaDev.CONNECTTYPE_USB:
            return rm.open_resource(str(addr))
        elif type == VisaDev.CONNECTTYPE_ETHERNET:
            return rm.open_resource("TCPIP::" + str(addr))
        elif type == VisaDev.CONNECTTYPE_SOCKET:
            return rm.open_resource("TCPIP::" + str(addr) + "::" + str(port) + "::SOCKET")