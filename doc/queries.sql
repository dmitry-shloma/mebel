/* Запись в таблицу tb_customer [заказчик] */
INSERT INTO mebel.tb_customer
    (fullname_or_name, registration_or_juridical_address, phone, email, information_source_id, note)
VALUES
    ('fullname_or_name', 'registration_or_juridical_address', 'phone', 'email', 9, 'note');

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
    
/* Выборка из таблицы tb_order [заказ] */
SELECT id, contract_number, contract_date, customer_species_id FROM mebel.tb_order WHERE customer_species_id IN
    (SELECT id FROM mebel.tb_customer_species);


CREATE TABLE IF NOT EXISTS tb_order (
    id INT PRIMARY KEY AUTO_INCREMENT,
    contract_number VARCHAR(20) COMMENT 'Номер договора',
    contract_date DATE COMMENT 'Дата договора',
    customer_species_id INT COMMENT 'Вид заказчика',
    customer_id INT COMMENT 'Заказчик',
    order_species_id INT COMMENT 'Вид заказа',
    furniture_type_id INT COMMENT 'Тип мебели',
    installation_date DATE NULL COMMENT 'Дата монтажа',
    is_exw BOOLEAN DEFAULT FALSE COMMENT 'Самовывоз',
    installation_address TINYTEXT NULL COMMENT 'Адрес монтажа',
    price DECIMAL(7,2) COMMENT 'Цена',
    initial_payment DECIMAL(7,2) COMMENT 'Первый взнос',
    balance DECIMAL(7,2) COMMENT 'Остаток',
    order_state_id INT DEFAULT 1 COMMENT 'Состояние заказа',
    order_state_change_history TEXT COMMENT 'История изменения состояния заказа',
    note TINYTEXT NULL COMMENT 'Примечание'
) COMMENT = 'Заказы';