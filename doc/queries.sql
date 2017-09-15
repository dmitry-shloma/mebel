/* Запись в таблицу customer [заказчик] */
INSERT INTO mebel.customer
    (fullname_or_shortname, registration_or_juridical_addr, phone, email, information_source_id, note)
VALUES
    ('Васек', '3-я улица Строителей', '79236756073', '1@mail.ru', 9, '');

/* Запись в таблицу natural_person [физическое лицо] */
INSERT INTO mebel.natural_person
    (id, birthday, ppt_series_number, ppt_issued_by, ppt_issued_starting_from)
VALUES
    (LAST_INSERT_ID(), '1983-09-28', '5204975552', 'УВД', '2004-04-14');

/* Запись в таблицу natural_person [юридическое лицо] */
#INSERT INTO mebel.juridical_person
#    (id, juridical_name, inn, ogrn_or_egrip, contact_person)
#VALUES
#    (LAST_INSERT_ID(), 'ООО ЮГОРИЯ', '123456', '123123123', 'Васисуалий');

/* Запись в таблицу contract [договор] */
INSERT INTO mebel.contract
    (number, conclusion_date, customer_type_id, customer_id, furniture_kind_id, assembly_address, price, initial_payment, remainder, delivery_date, note)
VALUES
    ('02/2017', CURRENT_DATE(), 1, LAST_INSERT_ID(), 2, 'tytyt', 9654.78, 123.1, 54.98, '2018-05-08', 'lk');