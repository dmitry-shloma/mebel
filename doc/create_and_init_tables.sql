DROP DATABASE IF EXISTS mebel;
CREATE DATABASE mebel;
USE mebel;

/* Создание структуры таблицы contract [договор] */
CREATE TABLE IF NOT EXISTS contract (
    id INT PRIMARY KEY AUTO_INCREMENT,
    number VARCHAR(20) COMMENT 'Номер договора',
    conclusion_date DATE COMMENT 'Дата заключения договора',
    customer_type_id INT COMMENT 'Тип заказчика',
    customer_id INT COMMENT 'Заказчик',
    furniture_kind_id INT COMMENT 'Вид мебели',
    assembly_address TINYTEXT COMMENT 'Адрес монтажа',
    price DECIMAL(7,2) COMMENT 'Цена',
    initial_payment DECIMAL(7,2) COMMENT 'Первоначальный взнос',
    remainder DECIMAL(7,2) COMMENT 'Остаток',
    delivery_date DATE COMMENT 'Дата сдачи заказа',
    note TINYTEXT COMMENT 'Примечание' NULL
) COMMENT = 'Договор';

/* Создание структуры таблицы customer_type [тип заказчика] */
CREATE TABLE IF NOT EXISTS customer_type (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(9) COMMENT 'Тип заказчика'
) COMMENT = 'Тип заказчика';

/* Инициализация таблицы customer_type [тип заказчика] */
INSERT INTO customer_type
	(name)
VALUES
	('Физ. лицо'),  # id | 1
    ('Юр. лицо');   # id | 2

/* Создание структуры таблицы customer [заказчик] */
CREATE TABLE IF NOT EXISTS customer (
    id INT PRIMARY KEY AUTO_INCREMENT,
    fullname_or_shortname TINYTEXT COMMENT 'ФИО/Краткое название',
    registration_or_juridical_address TINYTEXT COMMENT 'Адрес регистрации/Юридический адрес',
    phone VARCHAR(11) COMMENT 'Телефон',
    email TINYTEXT COMMENT 'Электронная почта' NULL,
    information_source_id INT COMMENT 'Источник информации',
    note TINYTEXT COMMENT 'Примечание' NULL
) COMMENT = 'Заказчик';

/* Создание структуры таблицы natural_person [физическое лицо] */
CREATE TABLE IF NOT EXISTS natural_person (
    id INT PRIMARY KEY,    # id устанавливается вручную, в зависимости от id из таблицы customer
    birthday DATE COMMENT 'Дата рождения',
    ppt_series_number VARCHAR(15) COMMENT 'Серия и номер паспорта',
    ppt_issued_by TINYTEXT COMMENT 'Орган, выдавший паспорт',
    ppt_issued_starting_from DATE COMMENT 'Дата выдачи паспорта'
) COMMENT = 'Физическое лицо';

/* Создание структуры таблицы juridical_person [юридическое лицо] */
CREATE TABLE IF NOT EXISTS juridical_person (
    id INT PRIMARY KEY,    # id устанавливается вручную, в зависимости от id из таблицы customer
    juridical_name VARCHAR(512) COMMENT 'Юридическое название',
    inn VARCHAR(15) COMMENT 'ИНН',
    ogrn_or_egrip VARCHAR(15) COMMENT 'ОГРН/ЕГРИП',
    contact_person TINYTEXT COMMENT 'Контактное лицо'
) COMMENT = 'Юридическое лицо';

/* Создание структуры таблицы information_source [источник информации] */
CREATE TABLE IF NOT EXISTS information_source (
	id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(128) COMMENT 'Наименование'
) COMMENT = 'Источник информации';

/* Инициализация таблицы information_source [источник информации] */
INSERT INTO information_source
	(name)
VALUES
	('наружная реклама'),       # id | 1
	('2ГИС'),                   # id | 2
    ('друзья'),                 # id | 3
	('ВКонтакте'),              # id | 4
	('Одноклассники'),          # id | 5
    ('Интернет-поиск'),         # id | 6
    ('партнерская программа'),  # id | 7
    ('СМИ'),                    # id | 8
    ('полиграфия'),             # id | 9
    ('другое');                 # id | 10
    
/* Создание структуры таблицы furniture_type [тип мебели] */
CREATE TABLE IF NOT EXISTS furniture_type (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(128) COMMENT 'Наименование'
) COMMENT = 'Тип мебели';

/* Инициализация таблицы furniture_type [тип мебели] */
INSERT INTO furniture_type
	(name)
VALUES
    ('для дома'),                           # id | 1
    ('для офиса'),                          # id | 2
    ('для дошкольных учреждений'),          # id | 3
    ('для образовательных учреждений'),     # id | 4
    ('для учреждений здравоохранения');     # id | 5

/* Создание структуры таблицы furniture_kind [вид мебели] */
CREATE TABLE IF NOT EXISTS furniture_kind (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(128) COMMENT 'Наименование',
    furniture_type_id INT COMMENT 'Тип мебели'
) COMMENT = 'Вид мебели';

/* Инициализация таблицы furniture_kind [вид мебели] */
INSERT INTO furniture_kind
	(name, furniture_type_id)
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

/* Создание внешних ключей таблицы contract [договор] */
ALTER TABLE contract
ADD FOREIGN KEY (customer_type_id) REFERENCES customer_type(id),
ADD FOREIGN KEY (customer_id) REFERENCES customer(id),
ADD FOREIGN KEY (furniture_kind_id) REFERENCES furniture_kind(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы customer [заказчик] */
ALTER TABLE customer
ADD FOREIGN KEY (information_source_id) REFERENCES information_source(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы natural_person [физическое лицо] */
ALTER TABLE natural_person
ADD FOREIGN KEY (id) REFERENCES customer(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы juridical_person [юридическое лицо] */
ALTER TABLE juridical_person
ADD FOREIGN KEY (id) REFERENCES customer(id)
ON UPDATE CASCADE ON DELETE CASCADE;

/* Создание внешних ключей таблицы furniture_kind [вид мебели] */
ALTER TABLE furniture_kind
ADD FOREIGN KEY (furniture_type_id) REFERENCES furniture_type(id)
ON UPDATE CASCADE ON DELETE CASCADE;