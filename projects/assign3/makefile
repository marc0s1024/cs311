CC = gcc
CFLAGS = -Wall -g
TARGET = test_piped
OBJS = piped.o test.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

piped.o: piped.c piped.h
	$(CC) $(CFLAGS) -c piped.c

test_piped.o: test.c piped.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f $(TARGET) $(OBJS)
