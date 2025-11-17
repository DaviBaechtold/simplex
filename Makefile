CC = gcc
CFLAGS = -Wall -Wextra -O2 -lm
TARGET = simplex
SOURCES = simplex.c
HEADERS = simplex.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET) exemplo.csv

.PHONY: all clean test
