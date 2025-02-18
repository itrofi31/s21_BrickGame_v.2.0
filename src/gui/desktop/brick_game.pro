QT += core gui widgets

TARGET = brick_game_desktop
TEMPLATE = app

# Пути к исходникам
INCLUDEPATH += \
    ../../brick_game/snake \
    ../../brick_game/tetris \

# Исходники Qt GUI
SOURCES += \
    main.cpp \
    main_window.cpp \
    snake_window.cpp \
    tetris_window.cpp

# Исходники бэкенда
SOURCES += \
    ../../brick_game/snake/model.cpp \
    ../../brick_game/snake/controller.cpp \
    ../../brick_game/tetris/game-logic.c \
    ../../brick_game/tetris/initialization.c \
    ../../brick_game/tetris/mem-free.c \
    ../../brick_game/tetris/figures.c

# Заголовочные файлы
HEADERS += \
    main_window.h \
    snake_window.h \
    tetris_window.h \
    ../../brick_game/snake/model.h \
    ../../brick_game/snake/controller.h \
    ../../brick_game/tetris/tetris.h

CONFIG += c++17

# Настройки компилятора для C файлов
QMAKE_CFLAGS += -x c
QMAKE_CXXFLAGS += -x c++

# Директории для сборки
DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui

# Специальные настройки для C файлов
c.name = GCC
c.input = SOURCES
c.dependency_type = TYPE_C
c.variable_out = OBJECTS
c.output = ${QMAKE_FILE_BASE}.o
c.commands = $${QMAKE_CC} $(QMAKE_CFLAGS) $(INCPATH) -c ${QMAKE_FILE_IN}