CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = program.exe
SOURCES = main.c \
       processing_arguments.c \
       scientific_work.c \
       sorting.c \
       stack.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ 

main.o: main.c processing_arguments.h scientific_work.h stack.h sorting.h
processing_arguments.o: processing_arguments.c processing_arguments.h
scientific_work.o: scientific_work.c scientific_work.h
sorting.o: sorting.c sorting.h
stack.o: stack.c stack.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f $(OBJECTS) $(TARGET)

rebuild: clean all