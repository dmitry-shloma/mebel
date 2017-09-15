# dirs
DESTDIR = $$PROJECT_BUILD_DIR/bin
OBJECTS_DIR = $$OUT_PWD/obj
MOC_DIR = $$OUT_PWD/moc
RCC_DIR = $$OUT_PWD/rcc
UI_DIR = $$OUT_PWD/ui

# compiler flags
QMAKE_CFLAGS += -std=c99
QMAKE_CXXFLAGS += -std=c++03
