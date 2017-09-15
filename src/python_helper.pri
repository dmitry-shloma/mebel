include(qmake_helper.pri)

# @brief get_python_version возвращает версию установленного Python
# @return если Python установлен, то возвращается версия в формате
# MAJOR.MINOR.PATCH, иначе пустая строка
defineReplace(get_python_version) {
    win32: error(qmake: windows platform not supported in the \
        function \'get_python_version()\')

    !is_app_installed(python): return ()
    unix: COMMAND = echo `python -V 2>&1 | grep -Po \'(?<=Python )(.+)\'`
    RESULT = $$system($$COMMAND)
    return ($$RESULT)
}

# @brief is_python_versions_installed определяет, соответствует ли
# версии установленного Python, одной из указанных версий
# @param VERSIONS список версий Python, разделенных запятыми или пробелами
# @return true - соответствует, иначе false
defineTest(is_python_versions_installed) {
    win32: error(qmake: windows platform not supported in the \
        function \'is_python_versions_installed(versions)\')

    VERSIONS = $$ARGS
    count(VERSIONS, 0): error(qmake: too few or to many arguments in the \
        function \'is_python_versions_installed(versions)\')

    VER = $$get_python_version()
    contains(VERSIONS, $$VER): return (true)
    return (false)
}
