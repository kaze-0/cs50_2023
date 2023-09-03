-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;
-- Theft took place at 10:15am, at Humphrey Street bakery with three witnesses
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- Within 10 minutes the thief left the bakery and got on a car.
-- The thief withdrawed money before 10:15am at ATM on Leggett Street
-- The thief phoned someone, and his accomplice purchased the earliesst flight one day after.

SELECT * FROM people
WHERE license_plate IN ( -- Cars exiting the parking from 10:15am to 10:25am.
    SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25
)
AND id IN ( -- Person use ATM on Leggett Street that day
    SELECT person_id FROM bank_accounts WHERE account_number in (
        SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28
    )
);
-- Found 4 people
--    id     name    phone_number      passport_number  lisence_plate
--"396669"	"Iman"	"(829) 555-5269"	"7049073643"	"L93JTIZ"
--"467400"	"Luca"	"(389) 555-5198"	"8496433585"	"4328GD8"
--"514354"	"Diana"	"(770) 555-1861"	"3592750733"	"322W7JE"
--"686048"	"Bruce"	"(367) 555-5533"	"5773159633"	"94KL13X"

SELECT * FROM flights WHERE id IN(   -- Find flight id
    SELECT flight_id FROM passengers WHERE passport_number IN(
        SELECT passport_number FROM people
        WHERE license_plate IN ( -- Cars exiting the parking from 10:15am to 10:25am.
            SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25
        )
        AND id IN ( -- Person use ATM on Leggett Street that day
            SELECT person_id FROM bank_accounts WHERE account_number in (
                SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28
            )
        )
    )
) AND year = 2021 AND month = 7 AND day = 29;
-- Then find destination_airport_id : 4, time: 8：20am, flights.id: 36

SELECT * FROM airports WHERE id = 4;
--  to 	New York City

SELECT * FROM passengers WHERE flight_id = 36 AND (passport_number = 7049073643 OR passport_number = 8496433585 OR passport_number = 3592750733 OR passport_number = 5773159633)
-- find 2 people taking that flight:
-- "467400"	"Luca"	"(389) 555-5198"
--"686048"	"Bruce"	"(367) 555-5533"

SELECT * FROM phone_calls
WHERE (caller = '(389) 555-5198' OR caller = '(367) 555-5533')
AND year = 2021 AND month = 7 AND day = 28;
-- only found Bruce made phone calls, so the thief is Luca

SELECT * FROM bank_accounts WHERE person_id IN( -- people who have a bank acconut
SELECT id FROM people WHERE phone_number IN ( -- id of those people
	SELECT receiver FROM phone_calls -- People Bruce called that day
	WHERE (caller = '(389) 555-5198' OR caller = '(367) 555-5533')
	AND year = 2021 AND month = 7 AND day = 28));
-- Only found one person id: 864400

SELECT name FROM people WHERE id = 864400;
-- The ACCOMPLICE is: Robin