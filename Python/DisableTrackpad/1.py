from os import system
from re import fullmatch, IGNORECASE
from time import sleep
import ctypes, sys


def isAdmin():
    try:
        return ctypes.windll.shell32.IsUserAnAdmin()
    except:
        return False


if not isAdmin():
    ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable,
                                        " ".join(sys.argv), None, 1)
    exit(0)

userInput = ""
devId = ""
while True:
    userInput = input("Keyboard/Trackpad/Exit?")
    if fullmatch("keyboard|key|k", userInput, IGNORECASE):
        print("Keyboard state:")
        # find it in Device Manager
        # & -> ^&
        devId = "ACPI\\HPQ8002\\4^&37026D19^&0"
        break
    elif fullmatch("trackpad|track|t", userInput, IGNORECASE):
        print("Trackpad state:")
        # find it in Device Manager
        devId = "ACPI\\ALP001A\\1"
        break
    elif fullmatch("exit|e|quit|q", userInput, IGNORECASE):
        print("exit")
        sleep(1)
        exit(0)

system("pnputil /enum-devices /instanceid " + devId)

userInput = ""
while True:
    userInput = input("ENable/Disable/Exit?")
    if fullmatch("enable|en", userInput, IGNORECASE):
        system("pnputil /enable-device " + devId)
        break
    elif fullmatch("disable|d", userInput, IGNORECASE):
        system("pnputil /disable-device " + devId)
        break
    elif fullmatch("exit|e|quit|q", userInput, IGNORECASE):
        print("exit")
        break

sleep(2)
exit(0)