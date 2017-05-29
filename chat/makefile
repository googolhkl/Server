CC = g++
SERVER = server
CLIENT = client
SEMAPHORE = static_semaphore
ALL = $(SERVER) $(CLIENT)
VERSION = -std=c++11

#THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread
THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread

all: $(ALL)

server: $(SERVER)

$(SERVER): server.o static_semaphore.o
	$(CC) $(VERSION) -o $(SERVER) $(SERVER).o $(SEMAPHORE).o $(THREAD)

server.o: server.cc
	$(CC) $(VERSION) -c -o $(SERVER).o $(SERVER).cc

static_semaphore.o: $(SEMAPHORE).cc
	$(CC) $(VERSION) -c -o $(SEMAPHORE).o $(SEMAPHORE).cc


client: $(CLIENT)

$(CLIENT): client.o
	$(CC) $(VERSION) -o $(CLIENT) client.o $(THREAD)

client.o: client.cc
	$(CC) $(VERSION) -c -o client.o client.cc


clean:
	rm *.o $(ALL)
