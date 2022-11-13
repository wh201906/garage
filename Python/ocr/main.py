import numpy as np
import pytesseract
import cv2
from matplotlib import pyplot as plt

# https://pyimagesearch.com/2022/02/28/multi-column-table-ocr/

# transform
# {
#     "key1": [a1, a2, a3],
#     "key2": [b1, b2, b3],
#     "key3": [c1, c2, c3],
#     "key4": [d1, d2, d3],
# }
# into
# [
#     {"key1": a1, "key2": b1, "key3": c1, "key4": d1},
#     {"key1": a2, "key2": b2, "key3": c2, "key4": d2},
#     {"key1": a3, "key2": b3, "key3": c3, "key4": d3},
# ]
def dictTransform(old: dict):
    lenList = [len(old[key]) for key in old.keys()]
    size = min(lenList)

    result = []
    for i in range(size):
        subDict = {}
        for k in old.keys():
            subDict[k] = old[k][i]
        result.append(subDict)

    return result


# disable axis, set margin to zero
def showImage(num=None):
    plt.figure(num)
    plt.subplots_adjust(left=0, bottom=0, right=1, top=1)
    plt.axis("off")

# show as normal graph
def showGraph(num=None):
    plt.figure(num)
    # plt.subplots_adjust(left=0, bottom=0, right=1, top=1)
    plt.axis("on")


# do ocr then show the result
def showOCR(img, options: str):
    results = pytesseract.image_to_data(
        img, config=options, lang="chi_sim+eng", output_type="dict"
    )

    textList = []
    resultImg = img.copy()
    for i in range(len(results["text"])):
        if results["level"][i] != 5:
            continue
        textList += results["text"][i]
        cv2.rectangle(
            resultImg,
            (results["left"][i], results["top"][i]),
            (
                results["left"][i] + results["width"][i],
                results["top"][i] + results["height"][i],
            ),
            0,
            1,
        )

    print(textList)
    showImage()
    plt.imshow(resultImg, "gray")


if __name__ == "__main__":
    inFile = "./test/1.png"

    # get grayscale image
    image = cv2.imread(inFile)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    showImage("gray")
    plt.imshow(gray, "gray")

    # get binary image
    bin = cv2.bitwise_not(gray)
    ret, bin = cv2.threshold(bin, 32, 255, cv2.THRESH_TOZERO)
    bin = cv2.bitwise_not(bin)
    showImage("bin")
    plt.imshow(bin, "gray")

    # show histogram
    grayHist = cv2.calcHist([gray], [0], None, [256], [0, 256])
    binHist = cv2.calcHist([bin], [0], None, [256], [0, 256])
    showGraph("grayHist")
    plt.plot(grayHist, color="r")
    plt.plot(binHist, color="g")

    showOCR(bin, "--psm 6")
    showOCR(gray, "--psm 6")

    # cv2.waitKey()
    plt.show()
