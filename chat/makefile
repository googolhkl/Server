CC = g++
SERVER = server
CLIENT = client
ALL = $(SERVER) $(CLIENT)

THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread

all: $(ALL)

server: $(SERVER)

$(SERVER): server.o
	$(CC) -o $(SERVER) server.o $(THREAD)

server.o: server.cc
	$(CC) -c -o server.o server.cc


client: $(CLIENT)

$(CLIENT): client.o
	$(CC) -o $(CLIENT) client.o $(THREAD)

client.o: client.cc
	$(CC) -c -o client.o client.cc


clean:
	rm *.o $(ALL)
