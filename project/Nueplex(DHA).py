from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import json
# Initialize the WebDriver
driver = webdriver.Chrome()

# Load the website
driver.get("https://www.nueplex.com/")

# Handle the popup to select the location (DHA, Askari IV, etc.)
WebDriverWait(driver, 20).until(
    EC.element_to_be_clickable((By.XPATH, "//a[@data-id='1' and contains(text(), 'DHA')]"))
).click()  # Select DHA or modify for other locations

# Wait for the page to load and display the movie schedules
WebDriverWait(driver, 20).until(
    EC.presence_of_element_located((By.CLASS_NAME, "movie-shedule"))
)

# Extract the movie showtimes
showtimes = driver.find_elements(By.CLASS_NAME, "movie-shedule")

showtimes_data = {
    "cinema_name" : "Nueplex DHA",
    "movies": []
}

for showtime_element in showtimes:
    movie_title = showtime_element.find_element(By.CLASS_NAME, "eq-height").text  # Adjust class name as needed
    times = showtime_element.find_elements(By.CLASS_NAME, "time")  # Adjust class name as needed
    times_list = [time.text for time in times]
    
    # Append movie and its showtimes to the data list
    showtimes_data["movies"].append({
        "title": movie_title,
        "showtimes": times_list
    })
    
    print(f"Movie Title: {movie_title}")
    print("Showtimes:")
    for time in times_list:
        print(f"  - {time}")
    print()
# Close the browser
driver.quit()


with open('showtimesDHA.json', 'w') as json_file:
    json.dump(showtimes_data, json_file, indent=4)
print("Showtimes data has been saved to 'showtimes.json'")
