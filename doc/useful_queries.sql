/* Определение макс. id из двух таблиц */
LOCK TABLES vega_mebel.natural_person WRITE, vega_mebel.juridical_person WRITE;   # блокировка таблиц, но можно и через транзакции
SET @id_max_value = 0;
SELECT id FROM (
    (SELECT id FROM natural_person ORDER BY id DESC LIMIT 1)
    UNION
    (SELECT id FROM juridical_person ORDER BY id DESC LIMIT 1)
) AS id_table ORDER BY id DESC LIMIT 1 INTO @id_max_value;
SET @id_max_value = @id_max_value + 1;
UNLOCK TABLES;

/* Выборка из таблицы по распостраненности имен */
SELECT name, COUNT(name) AS total, sex FROM clients WHERE sex = 'м' GROUP BY name /* HAVING total = 1 */ ORDER BY name;