# TODO: возможно стоит реализовать вывод расширенной информации, облегчающей
# поиск места ошибки при сообщении: one or more arguments in the function
# 'promotion_macro(name, value, mode)' are empty. Например, выводящей значение
# других агрументов

# @brief is_project_configured проверка, сконфигурирован ли проект
# @desc вызывается ТОЛЬКО из главного pro-файла проекта
# @return true - сконфигурирован, false - нет
defineTest(is_project_configured) {
    OUT_PWD_ = $$OUT_PWD
    !isEmpty(OUT_PWD_): return (true) # если проект сконфигурирован
    return (false)
}

# @brief init_qmake_cache инициализация (пересоздание) файла .qmake.cache
# @desc вызывается ОДИН РАЗ и ТОЛЬКО из главного pro-файла проекта
# param PROJECT_DIR директория проекта
# param PROJECT_BUILD_DIR директория сборки проекта
defineTest(init_qmake_cache) {
    PROJECT_DIR = $$1
    PROJECT_BUILD_DIR = $$2

    # проброс значения PROJECT_BUILD_DIR в функцию write_key_value(key, value),
    # т.к. при ее первом вызове, файл .qmake.cache еще не создан и значение
    # PROJECT_BUILD_DIR из него не считать,
    # при втором и последующих вызовах функции write_key_value(key, value), файл
    # .qmake.cache уже создан и значение PROJECT_BUILD_DIR считывается из него
    # export(PROJECT_BUILD_DIR)
    # НО, т.к. функции, при вызове одной из другой, обладают общей областью
    # видимости, делать экспорт не обязательно

    QMAKE_CACHE_FILENAME = $$PROJECT_BUILD_DIR/.qmake.cache
    exists($$QMAKE_CACHE_FILENAME) {
        unix: system(rm -rf $$QMAKE_CACHE_FILENAME)
        win32: system(DEL /Q /F $$replace(QMAKE_CACHE_FILENAME, /, \\))
    }

    write_key_value(PROJECT_DIR, $$PROJECT_DIR)
    write_key_value(PROJECT_BUILD_DIR, $$PROJECT_BUILD_DIR)
}

# @brief write_key_value запись ключа и его значения в файл .qmake.cache
# @desc см. описание функции init_qmake_cache(project_dir, project_build_dir)
# @param KEY ключ
# @param VALUE значение
defineTest(write_key_value) {
    KEY = $$1
    VALUE = $$2

    isEmpty(KEY)|isEmpty(VALUE): error(qmake: one or more arguments in the \
        function \'write_key_value(key, value)\' are empty)

    ARGS_ = $$ARGS
    !count(ARGS_, 2): error(qmake: too few or to many arguments in the \
        function \'write_key_value(key, value)\')

    system("echo $$KEY = $$VALUE >> $$PROJECT_BUILD_DIR/.qmake.cache")
}

# @brief promotion_macro продвижение макроса в файлы исходного кода
# (*.h, *.c, *.cpp) проекта
# @param NAME продвигаемое имя макроса
# @param VALUE значение продвигаемого макроса
# @param MODE режим продвижения (CONDITION, NUMBER или STRING)
defineReplace(promotion_macro) {
    NAME = $$1
    VALUE = $$2
    MODE = $$3
    isEmpty(NAME)|isEmpty(VALUE)|isEmpty(MODE): error(qmake: one or more \
        arguments in the function \'promotion_macro(name, value, mode)\' \
        are empty)

    ARGS_ = $$ARGS
    !count(ARGS_, 3): error(qmake: too few or to many arguments in the \
        function \'promotion_macro(name, value, mode)\')

    equals(MODE, CONDITION): return ($$VALUE $$NAME=$$VALUE)
    equals(MODE, NUMBER): return ($$NAME=$$VALUE)
    equals(MODE, STRING): return ($$NAME=\\\"$$VALUE\\\")
    error(qmake: \'$$MODE\' was not declared in this scope of \
        function \'promotion_macro(name, value, mode)\')
}

# @brief join_strings объединение нескольких строк в одну строку
# @param STRINGS строки для объединения, разделенные запятыми или пробелами
# @return результирующая строка
defineReplace(join_strings) {
    STRINGS = $$ARGS
    isEmpty(STRINGS): error(qmake: arguments in the \
        function \'join_strings(strings)\' are empty)

    for(STRING, STRINGS): RESULT_STRING = $$RESULT_STRING$$STRING
    return ($$RESULT_STRING)
}

# @brief is_app_installed проверка того, что указанное приложение установлено
# @desc_1 проверка состоит в вызове указанного приложения с ключом вывода
# информации о версии (почти все приложения для ОС семейства Microsoft Windows
# НЕ реализуют эту возможность, поэтому данная ОС НЕ поддерживается)
# и анализе возвращаемого значения
# @desc_2 man 1 bash, см. BASH_BUILTINS
# @param NAME имя приложения
# @return true - если приложение установлено, иначе - false
defineTest(is_app_installed) {
    win32: error(qmake: windows platform not supported in the \
        function \'is_app_installed(name)\')

    NAME = $$1
    isEmpty(NAME): error(qmake: argument in the \
        function \'is_app_installed(name)\' is empty)

    ARGS_ = $$ARGS
    !count(ARGS_, 1): error(qmake: too few or to many arguments in the \
        function \'is_app_installed(name)\')

    COMMAND = `command -v $$NAME >/dev/null 2>&1` && echo true || echo false

    RESULT = $$system($$COMMAND)
    return ($$RESULT)
}
