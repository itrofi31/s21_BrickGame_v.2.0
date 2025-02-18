CC = gcc -g -Wall -Wextra -Werror

CPP = g++ -g -std=c++17

TETRIS = brick_game/tetris/
SNAKE = brick_game/snake/
CLI = gui/cli/
QT_DIR = gui/desktop/
TARGET = brick_game_exec
QT_TARGET = brick_game_desktop

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN = xdg-open
	# Qt paths for Linux
	QMAKE = /usr/lib/qt5/bin/qmake
	QT_FLAGS = -spec linux-g++
else
	CHECK_FLAGS = -lcheck
	OPEN = open
	# Qt paths for MacOS
	QMAKE = qmake
	QT_FLAGS = -spec macx-g++
endif

TETRIS_BACK_SOURCES = $(wildcard $(TETRIS)*.c)
TETRIS_BACK_OBJECTS = $(TETRIS_BACK_SOURCES:.c=.o)

SNAKE_BACK_SOURCES = $(wildcard $(SNAKE)*.cpp)
SNAKE_BACK_OBJECTS = $(SNAKE_BACK_SOURCES:.cpp=.o)

FRONT_С_SOURCES = $(wildcard $(CLI)*.c)
FRONT_C_OBJECTS = $(FRONT_С_SOURCES:.c=.o)

FRONT_CPP_SOURCES = $(wildcard $(CLI)*.cpp)
FRONT_CPP_OBJECTS = $(FRONT_CPP_SOURCES:.cpp=.o)

ALL_OBJECTS = $(FRONT_C_OBJECTS) $(FRONT_CPP_OBJECTS)

# Qt specific
QT_SOURCES = $(wildcard $(QT_DIR)*.cpp)
QT_HEADERS = $(wildcard $(QT_DIR)*.h)

# Добавляем флаги для gtest
GTEST_DIR = /path/to/gtest
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Добавляем переменные для тестов
TEST_DIR = tests/
GTEST_FLAGS = -lgtest -lgtest_main -pthread
TEST_SOURCES = $(TEST_DIR)snake_tests.cpp $(SNAKE)model.cpp
TEST_TARGET = snake_tests

all: clean install tetris.a snake.a

# Добавляем цель для Qt версии
desktop: clean
	@mkdir -p $(QT_DIR)build
	@cd $(QT_DIR)build && $(QMAKE) ../brick_game.pro $(QT_FLAGS)
	@make -C $(QT_DIR)build
	@cp $(QT_DIR)build/brick_game_desktop.app/Contents/MacOS/brick_game_desktop ./
	@echo "┏======================================================┓"
	@echo "┃    desktop version build was successful.             ┃"
	@echo "┃    './brick_game_desktop' to run desktop version.    ┃"
	@echo "┗======================================================┛"

# Добавляем цель для запуска desktop версии
run_desktop: desktop
	@./brick_game_desktop

$(TARGET): tetris_backend.o gui.o snake_backend.o
	@$(CPP) $^ -lncurses -fsanitize=address -o $@ 


tetris_backend.o: $(TETRIS_BACK_OBJECTS)
	@ld -r $^ -o $@

snake_backend.o: $(SNAKE_BACK_OBJECTS)
	@ld -r $^ -o $@

gui.o: $(ALL_OBJECTS)
	@ld -r $^ -o $@

%.o: %.c
	@$(CC) -c $< -o $@

%.o: %.cpp
	@$(CPP) -c $< -o $@

tetris.a: $(TETRIS_BACK_OBJECTS)
	@ar rcs $@ $^

snake.a: $(SNAKE_BACK_OBJECTS)
	@ar rcs $@ $^

install: $(TARGET) 
	@rm -rf *.o
	@echo "┏=================================================┓"
	@echo "┃        The installation was successful.         ┃"
	@echo "┃      'make run' to start terminal version.      ┃"
	@echo "┃ 'make run_desktop' to start desktop version.    ┃"
	@echo "┗=================================================┛"

run: 
	@./$(TARGET)

uninstall: clean
	@rm -f $(TARGET) $(QT_TARGET)
	@echo "Program successfully uninstalled"

gcov_report: clean test 
	@$(CC) -coverage $(TETRIS_BACK_SOURCES) tests/test.c -o gcovreport $(CHECK_FLAGS)
	@./gcovreport
	@lcov -t "gcovreport" -o gcovreport.info -c -d .
	@genhtml -o report gcovreport.info
	@$(OPEN) report/./index.html

dvi: 
	@cd dvi && doxygen
	@$(OPEN) dvi/html/index.html

dist: 
	@cd ../ && mkdir -p dist
	@cp -r $(SNAKE) ../dist
	@cp -r $(CLI) ../dist
	@cp -r dvi ../dist/  
	@tar -czvf ../snake.tar.gz -C ../dist .
	@rm -rf ../dist snake
	@echo "Distribution package created: /snake.tar.gz"

test: test_snake
	@echo "All tests completed"

clean: clean_tetris clean_tests clean_dvi clean_dist clean_snake clean_desktop
	@echo "Cleaned..."

clean_tetris:
	@rm -rf $(CLI)*.o $(TETRIS)*.o *.o *.a
	
clean_snake:
	@rm -rf $(SNAKE)*.o 

clean_tests:
	@rm -rf  *.dSYM *.gcda *.gcno gcov* report test tests/*.c $(TEST_TARGET)

clean_dvi:
	@rm -rf dvi/html

clean_dist:
	@rm -rf ../snake.tar.gz

clean_desktop:
	@rm -rf $(QT_DIR)build

rebuild: clean all

# Добавляем цель для тестов
test_snake: $(TEST_SOURCES)
	@$(CPP) $^ -o $(TEST_TARGET) $(GTEST_FLAGS)
	@./$(TEST_TARGET)
	@echo "┏=================================================┓"
	@echo "┃        Snake tests completed successfully       ┃"
	@echo "┗=================================================┛"

test_tetris: tetris_backend.o
	@checkmk clean_mode=1 tests/*.check > tests/test.c 
	@$(CC) tests/test.c backend.o $(CHECK_FLAGS) -o test
	@./test

.PHONY: dvi