CC = g++
SERVER = server
CLIENT = client
ALL = $(SERVER) $(CLIENT)
VERSION = -std=c++11

#THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread
THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread

all: $(ALL)

server: $(SERVER)

$(SERVER): server.o
	$(CC) $(VERSION) -o $(SERVER) server.o $(THREAD)

server.o: server.cc
	$(CC) $(VERSION) -c -o server.o server.cc 


client: $(CLIENT)

$(CLIENT): client.o
	$(CC) $(VERSION) -o $(CLIENT) client.o $(THREAD)

client.o: client.cc
	$(CC) $(VERSION) -c -o client.o client.cc


clean:
	rm *.o $(ALL)
