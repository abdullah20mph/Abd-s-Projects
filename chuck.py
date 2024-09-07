#first you need to import request

import requests

def fetch_joke():
    url = 'https://api.chucknorris.io/jokes/random'
    
    try:
        response = requests.get(url)
        response.raise_for_status()
        
        joke_data = response.json()
        joke = joke_data['value']
        print(f"Chuck Norris Joke:\n{joke}")
        
    except requests.exceptions.RequestException as e:
        print(f"Error fetching Chuck Norris joke: {e}")
        
if __name__ == "__main__":
    fetch_joke()