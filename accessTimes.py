from selenium import webdriver
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
import requests
import random
import codecs
from time import sleep, time, strftime, localtime
from secret import *

# variables in secret.py
#
# (cookie)
# courseXPath = '/html/body/div/div[2]/div[3]/ul/li[6]/div[1]/a[1]'
# chapterXPath = /html/body/div[5]/div[1]/div[2]/div[3]/div[4]/div[3]/h3/a
# videoXPath
statisticXPath = '/html/body/div[4]/div/div/div[2]/ul/li[3]/a'
tableXPath = '/html/body/div[3]/div/div[2]/div/table'

waitTime = 8
driver = webdriver.Firefox()
WD = WebDriverWait(driver, waitTime, 0.5)
if 'cookie' not in locals().keys() or cookie is '':
    cookie = None

def rest():
    sleep(random.randint(2, waitTime))
    try:
        driver.get("http://255.255.255.255")
    except:
        pass
    sleep(random.randint(2, waitTime))

def login():
    global driver, cookie, WD
    driver.get("http://passport2.chaoxing.com/login")
    while True:
        sleep(0.5)
        try:
            print(driver.current_url)
            if 'http://i.mooc.chaoxing.com' in driver.current_url:
                cookie = driver.get_cookies()
                return True
        except:
            if cookie is None:
                return False


def gotoCourse():
    global driver, cookie, WD
    # Load
    url = "http://passport2.chaoxing.com/login"
    driver.get(url)
    driver.delete_all_cookies()
    for cookieItem in cookie:  # add cookie after driver.get()
        if cookieItem['domain'] in url:
            driver.add_cookie(cookieItem)

    url = 'http://i.mooc.chaoxing.com/space/index'
    driver.get(url)

    # Stage 1
    try:
        locator = (By.ID, 'frame_content')
        WD.until(EC.presence_of_element_located(locator))
        # important
        driver.switch_to.frame(driver.find_element_by_id('frame_content'))
        locator = (By.XPATH, courseXPath)
        WD.until(EC.presence_of_element_located(locator))
        url = driver.find_element_by_xpath(courseXPath).get_attribute("href")
        driver.get(url)
    except:
        return False


def task():
    global driver, cookie, WD

    gotoCourse()

    # Stage 2
    locator = (By.XPATH, chapterXPath)
    WD.until(EC.presence_of_element_located(locator))
    url = driver.find_element_by_xpath(chapterXPath).get_attribute("href")
    driver.get(url)

    # Stage 3
    locator = (By.ID, 'iframe')
    WD.until(EC.presence_of_element_located(locator))
    driver.switch_to.frame(driver.find_element_by_id('iframe'))
    # video = driver.find_element_by_xpath(videoXPath)
    # doesn't perform click as expected
    # ActionChains(driver).click(video).perform()

    rest()

def statistic():
    global driver, cookie, WD

    gotoCourse()
    locator = (By.XPATH, statisticXPath)
    WD.until(EC.presence_of_element_located(locator))
    url = driver.find_element_by_xpath(statisticXPath).get_attribute("href")
    driver.get(url)
    locator = (By.XPATH, tableXPath)
    WD.until(EC.presence_of_element_located(locator))
    table = driver.find_element_by_xpath(tableXPath)

    # print(table.text)
    rawRows = table.text.split('\n')
    # print(rawRows)
    rows = []
    for i in range(3):
        column = rawRows[i].split(' ')
        column.reverse()
        rows.append(column)
    id = rows[0].index('章节学习次数')

    rest()
    return (float(rows[1][id][:-1]), float(rows[2][id]))
    
random.seed()
if cookie is None:
    if login():
        print("Login succeed!")
        print("Cookies:")
        print(cookie)
    else:
        print("Failed to login!")
        exit()

rest()
startTime = time()
print("Task start at ", end='')
print(strftime("%Y-%m-%d %H:%M:%S", localtime(startTime)))

for i in range(200):
    taskTime = time()
    task()
    print("Counts:", i + 1, end=', ')
    print("Time Elapsed:", time() - taskTime, time() - startTime)
    if i % 50 is 0:
        (total, curr) = statistic()
        print("Current Process:", "Require:", total, "Current:", curr)
        if curr is total:
            break
print("Finished")