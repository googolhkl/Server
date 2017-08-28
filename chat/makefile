CC = g++
SERVER = server
CLIENT = client

$(SERVER): server.o
	$(CC) -o $(SERVER) $(SERVER).o 

server.o: server.cc
	$(CC) $(VERSION) -c -o $(SERVER).o $(SERVER).cc

client: $(CLIENT)

$(CLIENT): client.o
	$(CC) -o $(CLIENT) client.o


client.o: client.cc
	$(CC) -c -o client.o client.cc


clean:
	rm *.o $(SERVER) $(CLIENT)
