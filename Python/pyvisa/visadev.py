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