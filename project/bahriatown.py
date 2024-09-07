from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import json

# Initialize the WebDriver
options = webdriver.ChromeOptions()
options.add_argument("--incognito")
driver = webdriver.Chrome(options=options)

WebDriverWait(driver, 60).until(lambda d: d.execute_script("return document.readyState") == "complete")

# Load the website
driver.get("https://www.cinegoldplex.com/showtimes")

WebDriverWait(driver, 60).until(lambda d: d.execute_script("return document.readyState") == "complete")

# Wait for the dropdown menu to load and then select Karachi (value="3")
WebDriverWait(driver, 60).until(
    EC.element_to_be_clickable((By.ID, "branchSelect"))
)

# Find the dropdown and select Karachi by its value
branch_select = driver.find_element(By.ID, "branchSelect")
for option in branch_select.find_elements(By.TAG_NAME, 'option'):
    if option.text == 'Karachi':
        option.click()
        break

# Wait for the showtimes to load
WebDriverWait(driver, 60).until(
    EC.presence_of_element_located((By.ID, "showTimes-list"))
)

# Extract the movie names and showtimes
movies = driver.find_elements(By.CLASS_NAME, "showtime-section")

# Print or save the movie names and showtimes
showtimes_data = {
    "cinema": "Bahria Town",
    "movies": []
}

for showtime_element in movies:
    movie_title = showtime_element.find_element(By.TAG_NAME, "h3").text
    times = showtime_element.find_elements(By.CLASS_NAME, "showtime-timings")
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
# with open('showtimesBahria.json', 'w') as json_file:
#     json.dump(showtimes_data, json_file, indent=4)
# print("Showtimes data has been saved to 'showtimes.json'")
