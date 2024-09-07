from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time

driver = webdriver.Chrome()
for i in range(1,50):
# Load the page
    driver.get(f"https://books.toscrape.com/catalogue/page-{i}.html")

    elem = driver.find_elements(By.CLASS_NAME, "product_pod")

    for ele in elem:
       print(ele.text)
    print(f"{len(elem)} items found.")


# print(elem.get_attribute("outerHTML"))

#!The get_attribute("outerHTML") method in Selenium retrieves the entire HTML markup of an element, including the element itself and its contents.


driver.close()
# class="sg-col-20-of-24 s-result-item s-asin sg-col-0-of-12 sg-col-16-of-20 sg-col s-widget-spacing-small gsx-ies-anchor sg-col-12-of-16"