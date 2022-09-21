import sys
from os.path import exists, abspath, dirname, join, expanduser, sep
from os import system, environ, kill
from signal import SIGTERM
from subprocess import check_output, CalledProcessError
from psutil import process_iter

# Usage:
# python script.py <private key file 1> <private key file 2> ...
# The public key file and the private key file should be in the same directory
# the private key file should have no filename extension
# the public key file should have the same filename as the private key's, with ".pub" suffix

scriptBody = '''
read idx
pubkey="key::$(head -1 ${array[$idx]}.pub)"
echo $pubkey
'''

scriptPath = join(dirname(abspath(__file__)), "gen.sh")


def getProcList(name: str):
    result = {}
    for proc in process_iter(['pid', 'name']):
        procName = proc.info['name']
        if len(name) == 0 or procName.rsplit(".", 2)[0] == name:
            result[proc.info['pid']] = procName
    return result


if __name__ == '__main__':

    # get valid key path
    print("Checking key files", flush=True)
    pathArray = []
    for path in sys.argv[1:]:
        absolutePath = abspath(expanduser(path))
        if not exists(absolutePath):
            print(absolutePath, "not exists.", flush=True)
            continue
        if not exists(absolutePath + ".pub"):
            print(absolutePath + ".pub", "not exists.", flush=True)
            continue
        pathArray.append(absolutePath)

    if len(pathArray) == 0:
        print("No valid key files are found.", flush=True)
        sys.exit(1)
    else:
        for i, path in enumerate(pathArray):
            print("id: " + str(i) + ", key file:", path, flush=True)
    print("")

    # backup git config
    oldConfig = ""
    oldConfigValid = False
    try:
        oldConfig = check_output(
            "git config --global gpg.ssh.defaultKeyCommand",
            shell=True).decode()
        oldConfigValid = True
    except CalledProcessError:  # this happens if the config is not set.
        oldConfigValid = True

    # set git config
    system("git config --global gpg.ssh.defaultKeyCommand " +
           scriptPath.replace(sep, "/"))

    # generate script
    print("Generating shell script", flush=True)
    arrayStr = "declare -a array=("
    for path in pathArray[:-1]:
        arrayStr += "\"" + path + "\" "
    arrayStr += "\"" + pathArray[-1] + "\")\n"

    try:
        with open(scriptPath, "w") as f:
            f.write("#!/bin/bash\n")
            f.write("# " + str(pathArray) + "\n")  # save history
            f.write("\n")
            f.write(arrayStr)
            f.write(scriptBody)
    except Exception:
        print("Failed to generate script.", flush=True)
        sys.exit(1)

    print("Script generated at", flush=True)
    print(scriptPath, flush=True)
    print("")

    # start ssh-agent
    print("Starting ssh-agent", flush=True)
    oldProcList = getProcList("ssh-agent")
    output = check_output("ssh-agent", shell=True).decode()
    procList = {
        k: v
        for k, v in getProcList("ssh-agent").items() if k not in oldProcList
    }

    outputList = sum([line.split(";") for line in output.splitlines()], [])
    outputList = [s.strip() for s in outputList if "=" in s]
    for item in outputList:
        element = item.split("=")
        environ[element[0]] = element[1]
        print(item)

    print("New ssh-agent:")
    for k, v in procList.items():
        print(v, "pid:", k)
    print("All of them will be terminated after exiting the new bash.",
          flush=True)
    print("")

    # add private key to ssh-agent
    print("Adding private key", flush=True)
    for path in pathArray:
        system("ssh-add \"" + path + "\"")
    print("")

    # run a new shell with ssh-agent configured
    print("You will enter a new shell with ssh-agent.")
    print("Use \"exit\" plus Enter to exit.\n", flush=True)
    print("When signing with ssh,")
    print("please type the id(0,1,2,...) of the key you want to use,")
    print("Then press Enter to confirm.", flush=True)
    try:
        system("bash")
    except KeyboardInterrupt:
        pass

    # clean up
    print("You have exited the shell with ssh-agent.", flush=True)
    for k, v in procList.items():
        print("Killing", v, "pid:", k, flush=True)
        kill(k, SIGTERM)
    system("rm -f /tmp/.git_signing_key_tmp*")

    # restore git config
    if oldConfigValid:
        print("Restoring git config", flush=True)
        if len(oldConfig) == 0:
            system("git config --global --unset gpg.ssh.defaultKeyCommand ")
        else:
            system("git config --global gpg.ssh.defaultKeyCommand " +
                   oldConfig)
