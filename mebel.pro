include(src/qmake_helper.pri)

!is_project_configured(): \
    error(qmake: project is not yet configured)

init_qmake_cache()

TEMPLATE = subdirs

SUBDIRS = \
    src

OTHER_FILES += \
    README
