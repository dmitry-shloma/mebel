include(src/qmake_helper.pri)
include(src/projectinfo.pri)

is_project_configured(): init_qmake_cache()

TEMPLATE = subdirs

SUBDIRS = \
    src

OTHER_FILES += \
    README
