SELECT name FROM people
WHERE id IN (
    SELECT id FROM people JOIN stars ON people.id = stars.person_id
    WHERE stars.movie_id IN (
        SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958)
    )
) AND name IS NOT 'Kevin Bacon';