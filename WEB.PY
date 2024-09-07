from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from bs4 import BeautifulSoup

def scrape_cinepax():
    options = webdriver.ChromeOptions()
    options.add_argument('--headless')
    driver = webdriver.Chrome(options=options)  # Ensure chromedriver is in PATH
    
    print("Opening the Cinepax website")
    driver.get('https://cinepax.com/Browsing/Cinemas/Details/0000000002')
    
    try:
        print("Waiting for the show details to be present")
        WebDriverWait(driver, 30).until(
            EC.presence_of_element_located((By.CSS_SELECTOR, '.film-detail'))
        )
    except Exception as e:
        print(f"Timeout waiting for page to load: {e}")
        driver.quit()
        return
    
    soup = BeautifulSoup(driver.page_source, 'html.parser')

    movies = []
    for movie in soup.select('.film-detail'):
        title = movie.select_one('.title').get_text().strip()
        timings = [time.get_text().strip() for time in movie.select('.showtimes .btn')]
        movies.append({'title': title, 'timings': timings})

    driver.quit()
    
    print(movies)

scrape_cinepax()
