CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TARGET = s21_cat
COMMON_DIR = ../common
SOURCES = s21_cat.c $(COMMON_DIR)/common.c
HEADERS = s21_cat.h $(COMMON_DIR)/common.h
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

test: $(TARGET)
	@echo "Running basic tests..."
	@./test.sh

.PHONY: all clean rebuild test