import json
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

# Initialize Chrome WebDriver
driver = webdriver.Chrome()

# Navigate to the website
driver.get('https://www.thearena.com.pk/')

try:
    # Wait for the Arena Karachi link
    arena_link = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.LINK_TEXT, "Arena Karachi"))
    )
    
    # Scroll to the element and click using JavaScript
    driver.execute_script("arguments[0].scrollIntoView(true);", arena_link)
    time.sleep(1)
    driver.execute_script("arguments[0].click();", arena_link)
    
    # Wait for the Monday tab and click it
    monday_tab = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.XPATH, "//li[@data-date='2024-08-26']/a"))
    )
    
    # Scroll into view and click using JavaScript
    driver.execute_script("arguments[0].scrollIntoView(true);", monday_tab)
    time.sleep(1)
    driver.execute_script("arguments[0].click();", monday_tab)

    # Allow page to load
    time.sleep(2)
    
    # Scrape movie titles and showtimes
    movies = driver.find_elements(By.CLASS_NAME, 'movie_description')
    showtimes = driver.find_elements(By.CLASS_NAME, 'movie_times')

    # Collect data into a list of dictionaries
    showtimes_data = {
    "cinema_name" : "Nueplex DHA",
    "movies": []
}
    for movie, showtime in zip(movies, showtimes):
        title = movie.find_element(By.TAG_NAME, 'h3').text
        times = showtime.text
        showtimes_data["movies"].append({
        "title": title,
        "showtimes": times
    })
    
    # Save the scraped data to a JSON file
    with open('showtimesArena.json', 'w') as json_file:
        json.dump(showtimes_data, json_file, indent=4)
    
    print("Showtimes data has been saved to 'showtimesDHA.json'")

finally:
    # Close the browser
    driver.quit()
