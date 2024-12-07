select people.name as actors_in_toy_story from people join stars on stars.person_id = people.id join movies on movies.id = stars.movie_id where movies.title = 'Toy Story';
