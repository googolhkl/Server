CC = g++
TARGET = server
THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread

$(TARGET): server.o
	$(CC) -o $(TARGET) server.o $(THREAD)

server.o: server.cc
	$(CC) -c -o server.o server.cc $(THREAD)

clean:
	rm *.o $(TARGET)
