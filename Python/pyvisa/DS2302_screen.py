from DS2202A import DS2202A, VisaDev

if __name__ == '__main__':
    res = VisaDev.openProc(1, 'USB0::0x1AB1::0x04B0::DS2D234302864::INSTR')
    if res is None:
        exit(0)
    device = DS2202A(res)

    print(device.getName() + " connected")

    data = device.display_getScreen()
    with open("./DS2302.bmp", "wb") as f:
        f.write(device.display_getScreen())

    device.close()

