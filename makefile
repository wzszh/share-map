CC=gcc
CFLAGS=-Wall
TARGET=sharemap
SRC=example.c hashmap.c

all: $(TARGET)

$(TARGET): $(SRC)
		$(CC) $(CFLAGS) -o $@ $^


clean:
		rm -f $(TARGET)
		rm -f *.o




