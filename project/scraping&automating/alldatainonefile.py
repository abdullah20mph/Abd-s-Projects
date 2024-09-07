from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time

driver = webdriver.Chrome()
# Open a single file for writing all the text
with open("books_text.txt", "w", encoding="utf-8") as file:
    # Iterate through the first 50 pages
    for i in range(1, 51):  # Adjust the range if more pages are needed
        # Load the page
        driver.get(f"https://books.toscrape.com/catalogue/page-{i}.html")

        # Find all elements with class 'product_pod'
        elements = driver.find_elements(By.CLASS_NAME, "product_pod")

        # Iterate through the elements and write their text to the file
        for elem in elements:
            text = elem.text
            file.write(text + "\n")
            file.write("-" * 40 + "\n")  # Optional: separator for readability

# Close the browser
driver.close()
# print(elem.get_attribute("outerHTML"))

#!The get_attribute("outerHTML") method in Selenium retrieves the entire HTML markup of an element, including the element itself and its contents.


# class="sg-col-20-of-24 s-result-item s-asin sg-col-0-of-12 sg-col-16-of-20 sg-col s-widget-spacing-small gsx-ies-anchor sg-col-12-of-16"