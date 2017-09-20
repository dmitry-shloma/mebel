DROP DATABASE IF EXISTS mebel;
CREATE DATABASE mebel;
USE mebel;

/* Создание структуры таблицы tb_order [заказ] */
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

/* Создание структуры таблицы tb_customer_species [вид заказчика] */
CREATE TABLE IF NOT EXISTS tb_customer_species (
    id INT PRIMARY KEY AUTO_INCREMENT,
    species VARCHAR(9) COMMENT 'Вид'
) COMMENT = 'Вид заказчика';

/* Инициализация таблицы customer_species [вид заказчика] */
INSERT INTO tb_customer_species
	(species)
VALUES
    ('физ. лицо'),  -- id | 1
    ('юр. лицо');   -- id | 2

/* Создание структуры таблицы tb_customer [заказчик] */
CREATE TABLE IF NOT EXISTS tb_customer (
    id INT PRIMARY KEY AUTO_INCREMENT,
    fullname_or_name TINYTEXT COMMENT 'ФИО/Название',
    registration_or_juridical_address TINYTEXT COMMENT 'Адрес регистрации/Юридический адрес',
    phone VARCHAR(11) COMMENT 'Телефон',
    email TINYTEXT NULL COMMENT 'Электронная почта',
    information_source_id INT COMMENT 'Источник информации',
    note TINYTEXT NULL COMMENT 'Примечание'
) COMMENT = 'Заказчик';

/* Создание структуры таблицы tb_natural_person [физическое лицо] */
CREATE TABLE IF NOT EXISTS tb_natural_person (
    id INT PRIMARY KEY,    -- id устанавливается запросом, и соответствует макс. значению id из таблицы customer
    birth_date DATE COMMENT 'Дата рождения',
    ppt_series_and_number VARCHAR(15) COMMENT 'Серия и номер паспорта',
    ppt_issued_by TINYTEXT COMMENT 'Кем выдан',
    ppt_issue_date DATE COMMENT 'Дата выдачи'
) COMMENT = 'Физическое лицо';

/* Создание структуры таблицы tb_juridical_person [юридическое лицо] */
CREATE TABLE IF NOT EXISTS tb_juridical_person (
    id INT PRIMARY KEY,    -- id устанавливается запросом, и соответствует макс. значению id из таблицы customer
    juridical_name VARCHAR(512) COMMENT 'Юридическое название',
    inn VARCHAR(15) COMMENT 'ИНН',
    ogrn VARCHAR(15) COMMENT 'ОГРН',
    checking_account VARCHAR(15) COMMENT 'Расчетный счет',
    bank_name VARCHAR(15) COMMENT 'Название банка',
    corr_account VARCHAR(15) COMMENT 'Кор. счет',
    bik VARCHAR(15) COMMENT 'БИК',
    contact_person TINYTEXT COMMENT 'Контактное лицо'
) COMMENT = 'Юридическое лицо';

/* Создание структуры таблицы tb_information_source [источник информации] */
CREATE TABLE IF NOT EXISTS tb_information_source (
	id INT PRIMARY KEY AUTO_INCREMENT,
    source VARCHAR(128) COMMENT 'Источник'
) COMMENT = 'Источник информации';

/* Инициализация таблицы tb_information_source [источник информации] */
INSERT INTO tb_information_source
	(source)
VALUES
    ('наружная реклама'),       -- id | 1
    ('2ГИС'),                   -- id | 2
    ('друзья'),                 -- id | 3
    ('ВКонтакте'),              -- id | 4
    ('Одноклассники'),          -- id | 5
    ('Интернет-поиск'),         -- id | 6
    ('партнерская программа'),  -- id | 7
    ('СМИ'),                    -- id | 8
    ('полиграфия'),             -- id | 9
    ('другое');                 -- id | 10
    
/* Создание структуры таблицы tb_furniture_species [вид мебели] */
CREATE TABLE IF NOT EXISTS tb_furniture_species (
    id INT PRIMARY KEY AUTO_INCREMENT,
    species VARCHAR(128) COMMENT 'Вид'
) COMMENT = 'Вид мебели';

/* Инициализация таблицы tb_furniture_species [вид мебели] */
INSERT INTO tb_furniture_species
	(species)
VALUES
    ('для дома'),                           -- id | 1
    ('для офиса'),                          -- id | 2
    ('для дошкольных учреждений'),          -- id | 3
    ('для образовательных учреждений'),     -- id | 4
    ('для учреждений здравоохранения');     -- id | 5

/* Создание структуры таблицы tb_furniture_type [тип мебели] */
CREATE TABLE IF NOT EXISTS tb_furniture_type (
    id INT PRIMARY KEY AUTO_INCREMENT,
    type VARCHAR(128) COMMENT 'Тип',
    furniture_species_id INT COMMENT 'Вид мебели'
) COMMENT = 'Тип мебели';

/* Инициализация таблицы tb_furniture_type [тип мебели] */
INSERT INTO tb_furniture_type
	(type, furniture_species_id)
VALUES
    ('ванные комнаты', 1),
    ('гардеробные', 1),
    ('гостиные', 1),
    ('детские комнаты', 1),
    ('диваны', 1),
    ('комоды', 1),
    ('компьютерные столы', 1),
    ('кресла', 1),
    ('кухни', 1),
    ('обеденные зоны', 1),
    ('прихожие', 1),
    ('пуфы', 1),
    ('спальни', 1),
    ('шкафы', 1),
    ('шкафы-купе', 1),
    ('письменные столы', 2),
    ('ресепшны', 2),
    ('стеллажи для документов', 2),
    ('тумбы', 2),
    ('мебель для игровой комнаты', 3),
    ('развивающие стенки', 3),
    ('шкафы для раздевания', 3),
    ('парты', 4),
    ('трибуны', 4),
    ('мебель для кафедры', 4),
    ('медицинские кресла', 5), 
    ('медицинские посты', 5),
    ('мойки', 5),
    ('раздевалки для персонала', 5);

/* Создание структуры таблицы tb_order_species [вид заказа] */
CREATE TABLE IF NOT EXISTS tb_order_species (
    id INT PRIMARY KEY AUTO_INCREMENT,
    species VARCHAR(12) COMMENT 'Вид'
) COMMENT = 'Вид заказа';

/* Инициализация таблицы tb_order_species [вид заказа] */
INSERT INTO tb_order_species
	(species)
VALUES
    ('изготовление'),   -- id | 1
    ('продажа'),        -- id | 2
    ('услуга');         -- id | 3

/* Создание структуры таблицы tb_order_state [состояние заказа] */
CREATE TABLE IF NOT EXISTS tb_order_state(
    id INT PRIMARY KEY AUTO_INCREMENT,
    state VARCHAR(8) COMMENT 'Состояние'
) COMMENT = 'Состояние заказа';

/* Инициализация таблицы tb_order_state [состояние заказа] */
INSERT INTO tb_order_state
	(state)
VALUES
    ('принят'),     -- id | 1
    ('в работе'),   -- id | 2
    ('сдан');       -- id | 3

/* Создание внешних ключей таблицы tb_order [заказ] */
ALTER TABLE tb_order
ADD FOREIGN KEY (customer_species_id) REFERENCES tb_customer_species(id),
ADD FOREIGN KEY (customer_id) REFERENCES tb_customer(id),
ADD FOREIGN KEY (order_species_id) REFERENCES tb_order_species(id),
ADD FOREIGN KEY (furniture_type_id) REFERENCES tb_furniture_type(id),
ADD FOREIGN KEY (order_state_id) REFERENCES tb_order_state(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы tb_customer [заказчик] */
ALTER TABLE tb_customer
ADD FOREIGN KEY (information_source_id) REFERENCES tb_information_source(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы tb_natural_person [физическое лицо] */
ALTER TABLE tb_natural_person
ADD FOREIGN KEY (id) REFERENCES tb_customer(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы tb_juridical_person [юридическое лицо] */
ALTER TABLE tb_juridical_person
ADD FOREIGN KEY (id) REFERENCES tb_customer(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы tb_furniture_type [вид мебели] */
ALTER TABLE tb_furniture_type
ADD FOREIGN KEY (furniture_species_id) REFERENCES tb_furniture_species(id)
ON UPDATE CASCADE ON DELETE CASCADE;
