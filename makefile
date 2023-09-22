CC=gcc
CFLAGS=-Wall
TARGET=sharemap
SRC=example.c hashmap.c

all: $(TARGET) sharemap.so

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

sharemap.so: hashmap.c sharemap.c
	gcc $^ -o sharemap.so -fPIC -shared


clean:
	rm -f $(TARGET)
	rm -f *.o
	rm -f *.so




