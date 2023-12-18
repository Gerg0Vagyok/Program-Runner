CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0`
TARGET = runner
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
        $(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
        $(CC) -c -o $@ $< $(CFLAGS)

clean:
        rm -f $(TARGET) $(OBJ)
