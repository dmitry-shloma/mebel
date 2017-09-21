include(python_helper.pri)
include(qmake_helper.pri)

win32: error(qmake: windows platform not supported in this \
    module \'$$basename(_FILE_)\')

!is_python_versions_installed(2.4.3, 2.7.9): \
    error(qmake: python version is not supported)

# TODO: заменить $$1 и аналогичные на имена, как в qmake_helper.pri и др.

# @brief parse_project_name выделяет имя проекта и возвращает в формате макроса,
# т. е. в верхнем регистре и "-" (если есть) заменяет на "_"
# @param $$1 имя главного pro-файла проекта
defineReplace(parse_project_name) {
    USE_PROJECTINFO_PY = false

    USE_PROJECTINFO_PY {
        COMMAND = python -c \'import projectinfo; \
            print projectinfo.parse_project_name(\"$$1\")\'
    } else {
        SCRIPT_PY = $$join_strings( \
            "\\043!/usr/bin/env python\\n\\n" \
            "import os\\n\\n" \
            "def parse_project_name(pro_file_name):\\n" \
            "\\tbasename = os.path.basename(pro_file_name)\\n" \
            "\\tproject_name = os.path.splitext(basename)[0]\\n" \
            "\\tproject_name = project_name.upper()\\n" \
            "\\tproject_name = project_name.replace(\"-\", \"_\")\\n" \
            "\\treturn project_name\\n\\n" \
            "print(parse_project_name(\"$$1\"))")

        COMMAND = printf \'$$SCRIPT_PY\' | python
    }
    PROJECT_NAME = $$system($$COMMAND)
    return ($$PROJECT_NAME)
}

# @brief parse_project_version выделяет и возвращает указанную часть версии
# проекта
# @param $$1 версия проекта, в формате: $$MAJOR.$$MINOR.$$PATCH.$$BUILD
# @param $$2 часть версии проекта, которую необходимо вернуть. Допустимые
# значения: major, minor, patch, build
# @return в зависимости от $$2, если $$2 не задано или не существует,
# то сообщение об ошибке
defineReplace(parse_project_version) {
    # TODO: Eсли $$2 не задано, то сообщение об ошибке

    USE_PROJECTINFO_PY = false

    USE_PROJECTINFO_PY {
        COMMAND = python -c \'import projectinfo; \
        print projectinfo.parse_project_version(\"$$1\", \"$$2\")\'
    } else {
        SCRIPT_PY = $$join_strings( \
            "\\043!/usr/bin/env python\\n\\n" \
            "def parse_project_version(version, param):\\n" \
            "\\titems = version.split(\".\")\\n" \
            "\\tif param.lower() == \"major\":\\n" \
            "\\t\\treturn items[0]\\n" \
            "\\telif param.lower() == \"minor\":\\n" \
            "\\t\\treturn items[1]\\n" \
            "\\telif param.lower() == \"patch\":\\n" \
            "\\t\\treturn items[2]\\n" \
            "\\telif param.lower() == \"build\":\\n" \
            "\\t\\treturn items[3]\\n" \
            "\\telse:\\n" \
            "\\t\\tassert False\\n\\n" \
            "print(parse_project_version(\"$$1\", \"$$2\"))")

        COMMAND = printf \'$$SCRIPT_PY\' | python
    }
    PROJECT_VERSION = $$system($$COMMAND)
    return ($$PROJECT_VERSION)
}

# @brief parse_project_build_info выделяет и возвращает указанную часть
# информации о сборке проекта
# @param $$1 информация о сборке проекта, в формате:
# $$BUILD_DATETIME.$$BUILD_NUMBER~$$DESC
# @param $$2 часть версии проекта, которую необходимо вернуть. Допустимые
# значения: build_datetime, build_number, build_desc
# @return в зависимости от $$2, если $$2 не задано или не существует,
# то сообщение об ошибке
defineReplace(parse_project_build_info) {
    # TODO: $$2 если пусто то error

    USE_PROJECTINFO_PY = false

    USE_PROJECTINFO_PY {
        COMMAND = python -c \'import projectinfo; \
        print projectinfo.parse_project_build_info(\"$$1\", \"$$2\")\'
    } else {
        SCRIPT_PY = $$join_strings( \
            "\\043!/usr/bin/env python\\n\\n" \
            "def parse_project_build_info(build_info, param):\\n" \
            "\\tif param.lower() == \"build_datetime\":\\n" \
            "\\t\\treturn build_info.split(\".\")[0]\\n" \
            "\\telif param.lower() == \"build_number\":\\n" \
            "\\t\\treturn build_info.split(\".\")[1].split(\"~\")[0]\\n" \
            "\\telif param.lower() == \"build_desc\":\\n" \
            "\\t\\treturn build_info.split(\".\")[1].split(\"~\")[1]\\n\\n" \
            "print(parse_project_build_info(\"$$1\", \"$$2\"))")

        COMMAND = printf \'$$SCRIPT_PY\' | python
    }
    PROJECT_BUILD_INFO = $$system($$COMMAND)
    return ($$PROJECT_BUILD_INFO)
}

# @brief write_project_info запись информации о проекте в .qmake.cache
# @param PROJECT_NAME имя главного pro-файла проекта
# @param PROJECT_VERSION версия проекта, в формате: MAJOR.MINOR.PATCH.BUILD
# @param PROJECT_BUILD_INFO информация о сборке проекта, в формате:
# BUILD_DATETIME.BUILD_NUMBER~DESC
defineTest(write_project_info) {
    PROJECT_NAME = $$1
    PROJECT_VERSION = $$2
    PROJECT_BUILD_INFO = $$3

    !isEmpty(PROJECT_NAME) {
        write_key_value(PROJECT_NAME, $$parse_project_name($$PROJECT_NAME))
    }

    !isEmpty(PROJECT_VERSION) {
        write_key_value(PROJECT_MAJOR_VERSION, \
            $$parse_project_version($$PROJECT_VERSION, MAJOR))
        write_key_value(PROJECT_MINOR_VERSION, \
            $$parse_project_version($$PROJECT_VERSION, MINOR))
        write_key_value(PROJECT_PATCH_VERSION, \
            $$parse_project_version($$PROJECT_VERSION, PATCH))

        # т.к. $$PROJECT_BUILD_NUMBER используется в $$VERSION и в $$BUILD_INFO
        !infile($$PROJECT_BUILD_DIR/.qmake.cache, PROJECT_BUILD_NUMBER) {
            write_key_value(PROJECT_BUILD_NUMBER, \
                $$parse_project_version($$PROJECT_VERSION, BUILD))
        }
    }

    !isEmpty(PROJECT_BUILD_INFO) {
        write_key_value(PROJECT_BUILD_DATETIME, \
            $$parse_project_build_info($$PROJECT_BUILD_INFO, BUILD_DATETIME))
        !infile($$PROJECT_BUILD_DIR/.qmake.cache, PROJECT_BUILD_NUMBER) {
            write_key_value(PROJECT_BUILD_NUMBER, \
                $$parse_project_build_info($$PROJECT_BUILD_INFO, BUILD_NUMBER))
        }
        write_key_value(PROJECT_BUILD_DESC, \
            $$parse_project_build_info($$PROJECT_BUILD_INFO, BUILD_DESC))
    }
}
