from selenium import webdriver
import csv
import codecs

myDict = {}
resList = []

url1 = '***secret***'

xuehaoXpath = '***secret***'
xingmingXpath = '***secret***'
submitXpath = '***secret***'
resultXpath = '***secret***'


def loadName(filename):
    # 'utf-8-sig': UTF-8 with BOM
    with codecs.open(filename, 'r', 'utf-8-sig') as rfile:
        reader = csv.reader(rfile)
        for item in reader:
            myDict[item[0]] = item[1]


def getData():
    driver = webdriver.Firefox()

    for id, name in myDict.items():

        driver.get(url1)
        driver.implicitly_wait(15)

        xuehao = driver.find_element_by_xpath(xuehaoXpath)
        xuehao.clear()
        xuehao.send_keys(id)

        xingming = driver.find_element_by_xpath(xingmingXpath)
        xingming.clear()
        xingming.send_keys(name)

        driver.find_element_by_xpath(submitXpath).click()

        driver.implicitly_wait(15)

        result = driver.find_element_by_xpath(resultXpath).text

        if id in result:
            resList.append(result.split(' '))


def saveData(filename):
    with codecs.open(filename, 'a+', 'utf-8-sig') as wfile:
        writer = csv.writer(wfile)
        writer.writerows(resList)


loadName('data.csv')
print(myDict)

getData()
print(resList)

saveData('out.csv')
