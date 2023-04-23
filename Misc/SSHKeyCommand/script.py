import sys
from os.path import exists, abspath, dirname, join, expanduser, sep
from os import system, environ, kill, remove
from signal import SIGTERM
from subprocess import check_output, CalledProcessError
from ast import literal_eval
from re import fullmatch, IGNORECASE

# Usage:
# python script.py <private key file 1> <private key file 2> ...
# Or:
# python script.py # (requires last generated script as history)
# The public key file and the private key file should be in the same directory
# the private key file should have no filename extension
# the public key file should have the same filename as the private key's, with ".pub" suffix

scriptBody = '''
read idx
pubkey="key::$(head -1 ${array[$idx]}.pub)"
echo $pubkey
'''

scriptPath = join(dirname(abspath(__file__)), "gen.sh")

if __name__ == '__main__':
    tmp = []

    # detect if ssh-agent is running
    if "SSH_AGENT_PID" in environ.keys():
        tmp = input("ssh-agent is running. Continue? [y/N]")
        if not fullmatch("y|yes", tmp, IGNORECASE):
            print("Exited.", flush=True)
            sys.exit(0)

    # get valid key path
    useHistory = False
    if len(sys.argv) <= 1 and exists(scriptPath):
        try:
            with open(scriptPath, "r") as f:
                f.readline()
                tmp = literal_eval(f.readline()[2:])
                print("Using history from previous generated script\n")
                useHistory = True
        except Exception:
            pass
    if not useHistory:
        tmp = sys.argv[1:]

    print("Checking key files", flush=True)
    pathArray = []
    for path in tmp:
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
    output = check_output("ssh-agent", shell=True).decode()

    outputList = sum([line.split(";") for line in output.splitlines()], [])
    outputList = [s.strip() for s in outputList if "=" in s]
    for item in outputList:
        element = item.split("=")
        environ[element[0]] = element[1]
        print(item)

    print(
        "The pid of actual ssh-agent might be different from $SSH_AGENT_PID\n",
    )

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
    print("then press Enter to confirm.", flush=True)
    try:
        system("bash")
    except KeyboardInterrupt:
        pass

    # clean up
    print("You have exited the shell with ssh-agent.", flush=True)
    system("ssh-agent -k")
    system("rm -f /tmp/.git_signing_key_tmp*")
    system("rm -f " + environ["SSH_AUTH_SOCK"])

    # restore git config
    if oldConfigValid:
        print("Restoring git config", flush=True)
        if len(oldConfig) == 0:
            system("git config --global --unset gpg.ssh.defaultKeyCommand ")
        else:
            system("git config --global gpg.ssh.defaultKeyCommand " +
                   oldConfig)

    # Delete generated script
    tmp = input("Deleted generated script? [Y/n]")
    if not fullmatch("n|no", tmp, IGNORECASE):
        remove(scriptPath)
        print("Deleted", flush=True)
