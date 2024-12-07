-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.


-- checking who where in the bakery parking lot in that time frame
select p.name from people p join bakery_security_logs b on b.license_plate=p.license_plate where b.day=28 and b.month=7 and b.year=2023 and b.hour = 10 and b.minute between 15 and 25;

-- answer :

-- | Vanessa |
-- | Bruce   |
-- | Barry   |
-- | Luca    |
-- | Sofia   |
-- | Iman    |
-- | Diana   |
-- | Kelsey  |

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.


-- Who have withdrawing some money in ATM on Leggett Street
select p.name from people p join bank_accounts ba on ba.person_id = p.id join atm_transactions at on at.account_number = ba.account_number where at.day = 28 and at.month = 7 and at.year = 2023 and at.atm_location = 'Leggett Street';

-- | Bruce   |
-- | Kaelyn  |
-- | Diana   |
-- | Brooke  |
-- | Kenny   |
-- | Iman    |
-- | Luca    |
-- | Taylor  |
-- | Benista |

-- Intersect

-- between the first two answers the commun name between them to recognize the thief's name

select p.name from people p join bank_accounts ba on ba.person_id = p.id join atm_transactions at on at.account_number = ba.account_number where at.day = 28 and at.month = 7 and at.year = 2023 and at.atm_location = 'Leggett Street' intersect select p.name from people p join bakery_security_logs b on b.license_plate=p.license_plate where b.day=28 and b.month=7 and b.year=2023 and b.hour = 10 and b.minute between 15 and 25;
-- | Bruce |
-- | Diana |
-- | Iman  |
-- | Luca  |

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- the phone calls of 2023/07/28 and under 60s

select p.name, pc.caller from people p join phone_calls pc on pc.caller = p.phone_number where pc.year=2023 and pc.month = 7 and pc.day = 28 and pc.duration < 60;


-- | Sofia   | (130) 555-0289 |
-- | Kelsey  | (499) 555-9472 |
-- | Bruce   | (367) 555-5533 |
-- | Kelsey  | (499) 555-9472 |
-- | Taylor  | (286) 555-6063 |
-- | Diana   | (770) 555-1861 |
-- | Carina  | (031) 555-6622 |
-- | Kenny   | (826) 555-1652 |
-- | Benista | (338) 555-6650 |

-- intersect
-- between the three answers who has stayed

-- | Bruce   | (367) 555-5533 | (375) 555-8161 |
-- | Diana   | (770) 555-1861 | (725) 555-3243 |

select name from people where phone_number = "(375) 555-8161";

-- Bruce has called Robin

-- +-------+
-- | name  |
-- +-------+
-- | Robin |
-- +-------+

-- Diana has called Philip

select name from people where phone_number = "(725) 555-3243";


-- +--------+
-- |  name  |
-- +--------+
-- | Philip |
-- +--------+


-- flight (I noticed that Bruce have take the earliest flight)

-- +-----------+------------------------+
-- |   name    | destination_airport_id |
-- +-----------+------------------------+
-- | Doris     | 4                      |
-- | Sofia     | 4                      |
-- | Bruce     | 4                      |
-- +-----------+------------------------+


select city from airports where id = 4;

-- The city that Bruce escaped to is New York City with the id = 4 in airports

-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+


--- So Robin is the accomplice because bruce called Robin to take this flight
