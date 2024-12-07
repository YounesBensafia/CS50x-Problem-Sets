select people.name from people
join stars on stars.person_id = people.id
join movies on movies.id = stars.movie_id
where movies.title in (
select movies.title from movies
join stars on movies.id=stars.movie_id
join people on people.id = stars.person_id
where people.name = 'Kevin Bacon' and people.birth = 1958) and people.name != 'Kevin Bacon';
