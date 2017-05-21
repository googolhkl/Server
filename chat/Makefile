CC = g++
TARGET = test
THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread

$(TARGET): test.o
	$(CC) -o $(TARGET) test.o $(THREAD)

test.o: test.cc
	$(CC) -c -o test.o test.cc

clean:
	rm *.o $(TARGET)
