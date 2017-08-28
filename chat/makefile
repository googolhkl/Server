CC = g++
VERSION = -std=c++11
THREAD = -D_REENTARNT -lpthread

SERVER = server
CLIENT = client
ALL = $(SERVER) $(CLIENT)


all: $(ALL)
	
server: $(SERVER)

$(SERVER): server.o
	$(CC) $(VERSION) -o $(SERVER) $(SERVER).o

server.o: server.cc
	$(CC) $(VERSION) -c -o $(SERVER).o $(SERVER).cc

client: $(CLIENT)

$(CLIENT): client.o
	$(CC) $(VERSION) -o $(CLIENT) client.o $(THREAD)


client.o: client.cc
	$(CC) $(VERSION) -c -o client.o client.cc


clean:
	rm *.o $(SERVER) $(CLIENT)
