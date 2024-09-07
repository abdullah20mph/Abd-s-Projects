from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

# Initialize the Chrome WebDriver
driver = webdriver.Chrome()

# Load the LinkedIn login page
driver.get("https://www.linkedin.com/login")

# Wait for the page to load
time.sleep(2)

# Locate the email/phone input field and enter your email or phone number
email_input = driver.find_element(By.ID, "username")
email_input.send_keys("abdullah30mph@gmail.com")  # replace with your email

# Locate the password input field and enter your password
password_input = driver.find_element(By.ID, "password")
password_input.send_keys("RAkGtPuc")  # replace with your password

# Locate the sign-in button and click it
sign_in_button = driver.find_element(By.XPATH, "//button[@type='submit']")
sign_in_button.click()

# Wait until the search bar is visible and then perform a search
search_bar = WebDriverWait(driver, 10).until(
    EC.presence_of_element_located((By.CLASS_NAME, "search-global-typeahead__input"))
)
search_bar.send_keys("Folio3 HR", Keys.ENTER)

# Wait until the "See all people results" link is visible and then click it
see_all_people = WebDriverWait(driver, 10).until(
    EC.element_to_be_clickable((By.CSS_SELECTOR, "a.app-aware-link[href*='/search/results/people/?keywords=amazon%20hr']"))
)
see_all_people.click()

# Wait for the page to load
time.sleep(5)

# Continuously load profiles and process them
while True:
    profiles = driver.find_elements(By.CLASS_NAME, "reusable-search__result-container")

    for profile in profiles:
        try:
            # Locate the button within the profile section
            actions_div = profile.find_element(By.CLASS_NAME, "entity-result__actions")

            # Check if the button contains the text "Connect"
            connect_button = actions_div.find_element(By.XPATH, ".//span[text()='Connect']")

            if connect_button:
                connect_button.click()

                # Wait for the pop-up and click "Send without a note"
                send_without_note_button = WebDriverWait(driver, 5).until(
                    EC.element_to_be_clickable((By.XPATH, "//button[@aria-label='Send without a note']"))
                )
                send_without_note_button.click()

                # Give a slight delay to avoid triggering LinkedIn's rate limiter
                time.sleep(2)

        except Exception as e:
            # Skip profiles that don't have the "Connect" button or any other issues
            print("Skipping profile or an issue occurred:", e)

    # Scroll to the bottom of the page to load more profiles
    driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
    time.sleep(5)  # Wait for the new profiles to load

# Close the browser (optional if you want to stop the script manually)
# driver.close()
