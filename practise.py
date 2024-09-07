from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


driver = webdriver.Chrome()

#! 1ST EXAMPLE >>>>>>

# driver.get('https://books.toscrape.com/')
#!Click the element we want the sleenium to click .
# !We use the find_element_by_xpath method to find the element we want to click

# genre = WebDriverWait(driver,10).until(
#     EC.element_to_be_clickable((By.XPATH, "//a[contains(text(), 'Romance')]"))
# )
# genre.click()

#!finds the first and only element that it finds
# books = driver.find_element(By.CLASS_NAME,'product_pod')

# print(books.text)

#!finds all the elements found with that class name
#? books = driver.find_element(By.CLASS_NAME,'product_pod')
# for book in books:
#     print(book.text)



    
# print(f"Tag Name: {books.tag_name}")
# print(f"Class: {books.get_attribute('class')} /n ")
# print(f"HTML: {books.get_attribute('outerHTML')}")




# driver.close()

#!different fways of finding an element...

# element = driver.find_element(By.ID, "element_id")
# element = driver.find_element(By.NAME, "element_name")
# element = driver.find_element(By.CLASS_NAME, "class_name")
# element = driver.find_element(By.TAG_NAME, "tag_name")
# element = driver.find_element(By.LINK_TEXT, "Link Text")
# element = driver.find_element(By.PARTIAL_LINK_TEXT, "Partial Link")
# element = driver.find_element(By.CSS_SELECTOR, "css_selector")
# element = driver.find_element(By.XPATH, "xpath_expression")

#! 2ND Example >>>
driver.get('https://books.toscrape.com/')

genres = [
    'Travel', 'Mystery', 'Historical Fiction', 'Sequential Art', 'Classics',
    'Philosophy', 'Romance', 'Womens Fiction', 'Fiction', 'Childrens',
    'Religion', 'Nonfiction'
]

total_books = 0  # Initialize the total books counter

# Function to scrape all the pages for a particular genre
def scrape_all():
    global total_books  # Use the global variable to update the total count
    while True:
        books = driver.find_elements(By.CLASS_NAME, 'product_pod')
        total_books += len(books)  # Update the total books counter
        for book in books:
            print(book.text)
            print("-" * 40)
        
        try:
            # Locate the "Next" button and click it
            next_button = driver.find_element(By.XPATH, "//li[@class='next']/a[contains(text(), 'Next')]")
            next_button.click()
        except:
            # Break the loop if no "Next" button is found (end of pagination)
            break

# Loop through each genre and scrape all the books
for gen in genres:
    element = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.XPATH, f"//a[contains(text(), '{gen}')]"))
    )
    element.click()
    
    print(f"Scraping books for genre: {gen}")
    
    scrape_all()
    
    driver.back()

print(f"Total number of books scraped: {total_books}")

driver.close()