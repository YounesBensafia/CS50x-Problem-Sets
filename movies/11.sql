select movies.title from movies
join stars on movies.id = stars.movie_id
join people on people.id = stars.person_id
join ratings on movies.id = ratings.movie_id
where people.name = 'Chadwick Boseman' order by ratings.rating desc limit 5;
