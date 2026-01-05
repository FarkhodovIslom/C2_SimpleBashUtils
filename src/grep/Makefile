CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = s21_grep
SOURCES = s21_grep.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

test: $(TARGET)
	@echo "Running basic grep tests..."
	@./test_grep.sh || true

.PHONY: all clean rebuild test
