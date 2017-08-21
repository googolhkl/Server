CC = g++
SERVER = server
CLIENT = client
SEMAPHORE = static_semaphore
ALL = $(SERVER) $(CLIENT)
VERSION = -std=c++11

THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread

all: $(ALL)

server: $(SERVER)

$(SERVER): main_server.o server.o static_semaphore.o
	$(CC) $(VERSION) -o $(SERVER) $(SERVER).o $(SEMAPHORE).o main_server.o $(THREAD)

main_server.o: main_server.cc
	$(CC) $(VERSION) -c -o main_server.o main_server.cc

server.o: server.cc
	$(CC) $(VERSION) -c -o $(SERVER).o $(SERVER).cc

static_semaphore.o: $(SEMAPHORE).cc
	$(CC) $(VERSION) -c -o $(SEMAPHORE).o $(SEMAPHORE).cc


client: $(CLIENT)

$(CLIENT): main_client.o client.o
	$(CC) $(VERSION) -o $(CLIENT) client.o main_client.o $(THREAD)

main_client.o: main_client.cc
	$(CC) $(VERSION) -c -o main_client.o main_client.cc

client.o: client.cc
	$(CC) $(VERSION) -c -o client.o client.cc


clean:
	rm *.o $(ALL)
