import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import linear_kernel
# Пример данных об описании фильмов
data = {
'title': ['Фильм 1', 'Фильм 2', 'Фильм 3'],
'description': ['Описание фильма 1', 'Описание фильма 2',
'Описание фильма 3']
}
# Создание DataFrame
movies = pd.DataFrame(data)
# Векторизация описания фильмов
tfidf = TfidfVectorizer(stop_words='english')
tfidf_matrix = tfidf.fit_transform(movies['description'])
# Вычисление косинусной схожести
cosine_sim = linear_kernel(tfidf_matrix, tfidf_matrix)
# Функция для получения рекомендаций
def get_recommendations(title, cosine_sim=cosine_sim):
idx = movies[movies['title'] == title].index[0]
sim_scores = list(enumerate(cosine_sim[idx]))
sim_scores = sorted(sim_scores, key=lambda x: x[1],
reverse=True)
sim_scores = sim_scores[1:2]
movie_indices = [i[0] for i in sim_scores]
return movies['title'].iloc[movie_indices]
# Пример использования
movie_title = input("Введите название фильма: ")
recommendation = get_recommendations(movie_title)
print("Рекомендуемый фильм:", recommendation.values[0])