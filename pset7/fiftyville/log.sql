-- Keep a log of any SQL queries you execute as you solve the mystery.


-- vandalism 12:04 / shoplifting 03:01 two witness / theft 10:15 at Humphrey Street bakery / (DONE)Interviews with 3 witnesses
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2023;

-- (DONE)thief get into a car in the bakery parking lot and drive away within ten minutes of the theft (footage) / (DONE)thief withdraw some money on Leggett Street in the morning /
-- (DONE)leaving the bakery, they called someone for less than a minute. / Planned to take the earliest flight out of Fiftyville tomorrow (29/7/2023) asked the person to purchase the flight ticket
SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2023;

--POSSIBLE PLATES: 5P2BI95 / 94KL13X / 6P58WS2 / 4328GD8 / G412CB7 / L93JTIZ / 322W7JE / 0NTHK55
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND minute > 15 AND minute < 26 AND hour = 10;

-- use for people table AND phone_number = X
SELECT caller, receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2023 AND duration < 60;

-- possible names: Sofia / Diana / Kelsey / Bruce      receiver was not on the scene
SELECT name FROM people WHERE phone_number IN (SELECT caller, receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2023 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND minute > 15 AND minute < 26 AND hour = 10);

-- possible account numbers: 28500762 / 28296815 / 76054385 / 49610011 / 16153065 / 86363979 / 25506511 / 81061156 / 26013199
SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = 'Leggett Street';

-- possible names: Diana(3592750733)/ Bruce(5773159633)
SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2023 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND minute > 15 AND minute < 26 AND hour = 10) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = 'Leggett Street'));

-- Fiftyville Regional Airport / CSF / id: 8
SELECT full_name, abbreviation FROM airports WHERE city = 'Fiftyville';

-- id: 36 / destination id: 4 / hour: 8 / minute: 20
SELECT * FROM flights WHERE day = 28 AND month = 7 AND year = 2023 AND origin_airport_id = 8 ORDER BY hour ASC LIMIT 5;

-- all passport numbers from flight
SELECT passport_number FROM passengers WHERE flight_id = 36;

-- He run to NYC
SELECT city FROM airports WHERE id = 4;

-- all information about killer / Accomplice phone = (375) 555-8161
SELECT * FROM people WHERE name = 'Bruce' AND passport_number = 5773159633;

-- Robin is the Accomplice
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
