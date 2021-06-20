from selenium import webdriver
import codecs
from time import sleep
from secret import *

# variables in secret.py
#
# (cookie)
# courseXPath
# chapterXPath

waitTime = 8
driver = webdriver.Firefox()
if 'cookie' not in locals().keys():
    cookie = None

def login():
    global driver, cookie
    driver.get("http://passport2.chaoxing.com/login")
    while True:
        sleep(0.5)
        try:
            if str(driver.current_url).find('http://i.mooc.chaoxing.com') is not -1:
                cookie = driver.get_cookies()
                print(cookie)
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
        print("Current cookie:")
        print(cookieItem)
        if cookieItem['domain'] in url:
            driver.add_cookie(cookieItem)

    # Stage 1
    driver.get('http://i.mooc.chaoxing.com/space/index')
    driver.implicitly_wait(waitTime)
    driver.switch_to.frame(driver.find_element_by_id('frame_content'))  # important
    url = driver.find_element_by_xpath(courseXPath).get_attribute("href")

    # Stage 2
    driver.get(url)
    driver.implicitly_wait(waitTime)
    url = driver.find_element_by_xpath(chapterXPath).get_attribute("href")

    # Stage 3
    driver.get(url)
    driver.implicitly_wait(waitTime)

if cookie is None:
    login()
task()
sleep(50)