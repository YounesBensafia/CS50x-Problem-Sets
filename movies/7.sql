Select title, ratings.rating from movies join ratings on ratings.movie_id = movies.id where movies.year = 2010 order by ratings.rating desc, title asc;
