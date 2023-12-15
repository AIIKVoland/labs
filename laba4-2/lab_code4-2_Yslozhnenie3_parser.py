import requests
from bs4 import BeautifulSoup

def get_bbc_news(query):
    # Получаем RSS-ленту BBC News.
    response = requests.get("https://feeds.bbci.co.uk/news/rss.xml")
    soup = BeautifulSoup(response.content, "xml")

    # Получаем список новостей из RSS-ленты.
    news_items = soup.find_all("item")

    # Фильтруем новости по запросу.
    filtered_news_items = []
    for news_item in news_items:
        if query in news_item.find("title").text:
            filtered_news_items.append(news_item)

    return filtered_news_items

if __name__ == "__main__":
    # Запрашиваем новости об интересующейся теме.
    query = input("Введите тему: ")
    news_items = get_bbc_news(query)

    # Выводим список новостей.
    for news_item in news_items:
        print(news_item.find("title").text)