from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time

# Initialize the WebDriver
driver = webdriver.Chrome()

# Load the page
driver.get("https://www.thearena.com.pk/")

# Get the HTML content of the page
page_html = driver.page_source

# Print the HTML content (optional)
print(page_html)
# Save the HTML content to a file
with open("arena.html", "w", encoding="utf-8") as file:
    file.write(page_html)

# Optional: Interact with specific elements on the page
# For example, if you want to find showtime elements:
# elem = driver.find_elements(By.CLASS_NAME, "show-time-li")

# for ele in elem:
#     d = ele.get_attribute("outerHTML")
#     print(ele.text)
#     # You can also save this content to a file or process it further

# Close the browser
driver.close()
