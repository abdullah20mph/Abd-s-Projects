from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import json

# Initialize the WebDriver
driver = webdriver.Chrome()

# Load the website

driver.get("https://cinepax.com/Browsing/Cinemas/Details/0000000002")

# film-showtimes


# # Wait for the page to load and display the movie schedules
WebDriverWait(driver, 10).until(
    EC.presence_of_element_located((By.CLASS_NAME, "film-showtimes"))
)

# Extract the movie showtimes
showtimes = driver.find_elements(By.CLASS_NAME, "film-showtimes")

showtimes_data = {
    "cinema" : "Cinepax Ocean Mall",
    "movies": []
}

for showtime_element in showtimes:
    movie_title = showtime_element.find_element(By.CLASS_NAME, "film-title").text  # Adjust class name as needed
    times = showtime_element.find_elements(By.CLASS_NAME, "session-time ")  # Adjust class name as needed
    times_list = [time.text for time in times]
    
    # Append movie and its showtimes to the data list
    showtimes_data["movies"].append({
        "title": movie_title,
        "showtimes": times_list
    })
    
   
# Close the browser
driver.quit()


with open('showtimesCinepax.json', 'w') as json_file:
    json.dump(showtimes_data, json_file, indent=4)
print("Showtimes data has been saved to 'showtimes.json'")
