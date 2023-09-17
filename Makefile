# Compiler and Flags
CC=gcc
CFLAGS=-Wall -g

# Executable Name
TARGET=calculator

# Source Files
SRC=dataStructures.c expressionParser.c doubleStack.c graph.c graphics.c polishNotation.c

# Object Files
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
