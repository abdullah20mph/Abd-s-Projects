from bs4 import BeautifulSoup
import os
import pandas as pd

d = {'title': [], 'price':[],'link':[]}

for file in os.listdir("C:/webscrap/python/work/data"):
     try:
        with open(f"C:/webscrap/python/work/data/{file}") as f:

         html_doc = f.read()
        soup = BeautifulSoup(html_doc, 'html.parser')
        t = soup.find("h3").get_text()
        price = soup.find("p", class_="price_color").get_text()
        link = soup.find("a")["href"]  # Example selector for link
        newLink = "https://books.toscrape.com/catalogue/" + link
        print(t,price,newLink)
        d["title"].append(t)
        d["price"].append(price)
        d["link"].append(newLink)
     except Exception as e:
        print(e)
    
df = pd.DataFrame(data=d)
df.to_csv('book.csv')
    