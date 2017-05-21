CC = g++
TARGET = test

$(TARGET): test.o
	$(CC) -o $(TARGET) test.o

test.o: test.cc
	$(CC) -c -o test.o test.c

clean:
	rm *.o $(TARGET)
