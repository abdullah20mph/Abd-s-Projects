# from bs4 import BeautifulSoup
# import requests
# import time

# # print("Put some unfamiliar skills of ur own")
# # unfamiliar = input('')
# # print("filtering unfamiliar skills")
# #try to take  mutpiple inputs as a challenge

# def find_jobs():
    
#   html_text = requests.get('https://www.timesjobs.com/  candidate/job-search.html?searchType=personalizedSearch&  from=submit&searchTextSrc=as&searchTextText=Python&  txtKeywords=Python&txtLocation=').text
#   # print(html_text)
#   soup = BeautifulSoup(html_text,'lxml')
#   # jobs = soup.find_all('li', class_='clearfix job-bx   wht-shd-bx')
#   jobs = soup.find_all('li', class_='clearfix job-bx   wht-shd-bx')
#   for job in jobs:
#       publish_Date = job.find('span',class_='sim-posted').  span.text
#       if 'few' in publish_Date:
          
#           company_name = job.find('h3',       class_='joblist-comp-name').text.replace(' ','')
#           skills = job.find('span',class_='srp-skills').text.   replace('  ','')
#           if unfamiliar not in skills:
          
#           # print(publish_Date)
          
#               print(f' Company Name: {company_name.strip()} ')
#               print(f' Skills: {skills.strip()}')
#               ('')
# if __name__ == '__main__':
#     while True:
#         find_jobs()
#         time.sleep(600)

from bs4 import BeautifulSoup
import requests
import time

def find_jobs(unfamiliar_skills):
    url = 'https://www.timesjobs.com/candidate/job-search.html?searchType=personalizedSearch&from=submit&searchTextSrc=as&searchTextText=Python&txtKeywords=Python&txtLocation='
    html_text = requests.get(url).text
    soup = BeautifulSoup(html_text, 'lxml')
    jobs = soup.find_all('li', class_='clearfix job-bx wht-shd-bx')
    
    for job in jobs:
        publish_date = job.find('span', class_='sim-posted').span.text
        if 'few' in publish_date:
            company_name = job.find('h3', class_='joblist-comp-name').text.strip().replace('  ', ' ')
            skills = job.find('span', class_='srp-skills').text.strip().replace('  ', ' ')
            
            if not any(skill in skills for skill in unfamiliar_skills):
                print(f'Company Name: {company_name}')
                print(f'Skills: {skills}')
                print('')

if __name__ == '__main__':
    unfamiliar_skills = input("Enter unfamiliar skills separated by commas: ").split(',')
    unfamiliar_skills = [skill.strip() for skill in unfamiliar_skills]  # Clean up any extra spaces

    while True:
        find_jobs(unfamiliar_skills)
        time.sleep(600)  # Wait for 10 minutes before running again
