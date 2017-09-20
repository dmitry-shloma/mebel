/* Запись в таблицу tb_customer [заказчик] */
INSERT INTO mebel.tb_customer
    (fullname_or_name, registration_or_juridical_address, phone, email, information_source_id, note)
VALUES
    ('Васек', '3-я улица Строителей', '79236756073', '1@mail.ru', 9, '');

/* Запись в таблицу tb_natural_person [физическое лицо] */
INSERT INTO mebel.tb_natural_person
    (id, birth_date, ppt_series_and_number, ppt_issued_by, ppt_issue_date)
VALUES
    (LAST_INSERT_ID(), '1983-09-28', '5204975552', 'УВД', '2004-04-14');

/* Запись в таблицу tb_juridical_person [юридическое лицо] */
-- INSERT INTO mebel.tb_juridical_person
--    (id, juridical_name, inn, ogrn, checking_account, bank_name, corr_account, bik, contact_person)
-- VALUES
--    (LAST_INSERT_ID(), 'ООО ЮГОРИЯ', '123456', '123123123', '123', 'banka', '324', 'fg', 'Васисуалий');

/* Запись в таблицу tb_order [заказ] */
INSERT INTO mebel.tb_order
    (contract_number, contract_date, customer_species_id, customer_id, order_species_id, furniture_type_id, installation_date, is_exw, installation_address, price, initial_payment, balance, order_state_id, order_state_change_history, note)
VALUES
    ('02/2017', CURRENT_DATE(), 1, LAST_INSERT_ID(), 2, 4, CURRENT_DATE(), false, 'на окраине', '999.99', '666.6', '345', 1, 'hist', 'note');