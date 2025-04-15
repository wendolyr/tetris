CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c11 
SANFLAG=#-fsanitize=address -g

SHELLNAME:=$(shell uname)
ifeq ($(SHELLNAME), Linux)
	LDFLAGS = -lcheck -lsubunit -lm
else ifeq ($(SHELLNAME), Darwin)
	LDFLAGS = -lcheck
endif

BIN = tetris

MAIN = $(BIN).c
MAIN_OBJ = $(BIN).o

BUILD_DIR = ./build
LOGS_DIR = ./tests/logs

FRONT_DIR = ./gui/cli
FRONT_DIR_OBJ = $(FRONT_DIR)/obj

BACK_DIR = ./brick_game/$(BIN)
BACK_DIR_OBJ = $(BACK_DIR)/obj

TEST_DIR = ./tests
TEST_DIR_OBJ = $(TEST_DIR)/obj

LIB = $(BACK_DIR)/$(BIN)_backend.a

BACK_SRC = $(wildcard $(BACK_DIR)/*.c)
BACK_OBJ = $(patsubst $(BACK_DIR)/%.c, $(BACK_DIR_OBJ)/%.o, $(BACK_SRC))

FRONT_SRC = $(wildcard $(FRONT_DIR)/*.c)
FRONT_OBJ = $(patsubst $(FRONT_DIR)/%.c, $(FRONT_DIR_OBJ)/%.o, $(FRONT_SRC))

TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR_OBJ)/%.o, $(TEST_SRC))

DIST_DIR = dist
DIST_NAME = brick_game_v1.0.tar.gz
DIST_FILES = $(BACK_DIR) $(FRONT_DIR) headers Makefile Doxyfile *.c


all: uninstall install

$(FRONT_DIR_OBJ) $(BACK_DIR_OBJ) $(TEST_DIR_OBJ):
		@mkdir -p $@

$(LIB) : $(BACK_OBJ)
		@ar rcs $@ $^

$(BACK_DIR_OBJ)/%.o: $(BACK_DIR)/%.c | $(BACK_DIR_OBJ)
	$(CC) $(CFLAGS) -c $(SANFLAG) $< -o $@

$(FRONT_DIR_OBJ)/%.o: $(FRONT_DIR)/%.c | $(FRONT_DIR_OBJ)
	$(CC) $(CFLAGS) -c $(SANFLAG) $< -o $@

$(TEST_DIR_OBJ)/%.o: $(TEST_DIR)/%.c | $(TEST_DIR_OBJ)
	$(CC) $(CFLAGS) -c $(SANFLAG) $< -o $@

install: clean $(LIB) $(FRONT_OBJ) $(MAIN_OBJ)
		@mkdir -p $(BUILD_DIR)
		@$(CC) $(CFLAGS) $(SANFLAG) $(FRONT_OBJ) $(MAIN_OBJ) $(LIB) -o $(BUILD_DIR)/$(BIN) -lncurses

uninstall: clean
		@rm -rf $(BUILD_DIR)

play:
		@$(BUILD_DIR)/$(BIN)

test: clean $(LIB) $(TEST_OBJ)
		@$(CC) $(CFLAGS) $(TEST_OBJ) $(LIB) -o $(TEST_DIR)/tests $(LDFLAGS)
		@$(TEST_DIR)/tests

gcov_report: CFLAGS += -coverage
gcov_report: uninstall test
		@mkdir -p $(LOGS_DIR)
		@lcov --capture --directory . --output-file $(LOGS_DIR)/coverage.info
		@genhtml $(LOGS_DIR)/coverage.info --output-directory $(LOGS_DIR)
		@open $(LOGS_DIR)/index.html

dvi:
		@rm -rf doxygen
		@doxygen && open doxygen/html/index.html

dist: clean
		@echo "Creating archive..."
		@mkdir -p $(DIST_DIR)
		@tar -czf $(DIST_DIR)/$(DIST_NAME) $(DIST_FILES)
		@echo "Archive created!"


valgrind: test
		@clear
		@valgrind --tool=memcheck --leak-check=yes $(TEST_DIR)/tests

clang:
		@echo "Checking clang-format..."
		@cp ../materials/linters/.clang-format .
		@clang-format -n *.c $(BACK_DIR)/*.c $(FRONT_DIR)/*.c ./headers/*.h ./tests/*.c ./tests/*.h
		@echo "Checking complete!"

clean:
		@rm -rf $(FRONT_DIR_OBJ) $(BACK_DIR_OBJ) $(TEST_DIR_OBJ) $(TEST_DIR)/tests $(DIST_DIR) $(LIB) *.o doxygen $(LOGS_DIR) .clang-format
