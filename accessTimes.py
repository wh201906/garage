from selenium import webdriver
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
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

waitTime = 8
driver = webdriver.Firefox()
if 'cookie' not in locals().keys() or cookie is '':
    cookie = None


def login():
    global driver, cookie
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


def task():

    global driver, cookie
    # Load
    url = "http://passport2.chaoxing.com/login"
    driver.get(url)
    driver.delete_all_cookies()
    for cookieItem in cookie:  # add cookie after driver.get()
        if cookieItem['domain'] in url:
            driver.add_cookie(cookieItem)

    WD = WebDriverWait(driver, waitTime, 0.5)

    # Stage 1
    url = 'http://i.mooc.chaoxing.com/space/index'
    driver.get(url)
    try:
        locator = (By.ID, 'frame_content')
        WD.until(EC.presence_of_element_located(locator))
        # important
        driver.switch_to.frame(driver.find_element_by_id('frame_content'))
        locator = (By.XPATH, courseXPath)
        WebDriverWait(driver, waitTime,
                      0.5).until(EC.presence_of_element_located(locator))
        url = driver.find_element_by_xpath(courseXPath).get_attribute("href")
    except:
        return False

    # Stage 2
    driver.get(url)
    locator = (By.XPATH, chapterXPath)
    WD.until(EC.presence_of_element_located(locator))
    url = driver.find_element_by_xpath(chapterXPath).get_attribute("href")

    # Stage 3
    driver.get(url)
    locator = (By.ID, 'iframe')
    WD.until(EC.presence_of_element_located(locator))
    driver.switch_to.frame(driver.find_element_by_id('iframe'))
    # video = driver.find_element_by_xpath(videoXPath)
    # doesn't perform click as expected
    # ActionChains(driver).click(video).perform()

    sleep(random.randint(2, waitTime))
    try:
        driver.get("http://255.255.255.255")
    except:
        pass
    sleep(random.randint(2, waitTime))


random.seed()
if cookie is None:
    if login():
        print("Login succeed!")
        print("Cookies:")
        print(cookie)
    else:
        print("Failed to login!")
        exit()

startTime = time()
print("Task start at ", end='')
print(strftime("%Y-%m-%d %H:%M:%S", localtime(startTime)))
for i in range(200):
    taskTime = time()
    task()
    print("Counts:", i + 1, end=', ')
    print("Time Elapsed:", time() - taskTime, time() - startTime)
print("Finished")