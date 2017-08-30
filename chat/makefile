CC = g++
SERVER = server
CLIENT = client
SEMAPHORE = static_semaphore
ALL = $(SERVER) $(CLIENT)
VERSION = -std=c++11

THREAD = -D_REENTRANT -lpthread # -D_REENTRANT: Thread safe, # -lpthread: for thread

all: $(ALL)

$(SERVER): main_server.o server.o static_semaphore.o user.o user_controller.o
	$(CC) $(VERSION) -o $(SERVER) $(SERVER).o $(SEMAPHORE).o main_server.o user.o user_controller.o $(THREAD)

main_server.o: main_server.cc
	$(CC) $(VERSION) -c -o main_server.o main_server.cc

server.o: server.cc
	$(CC) $(VERSION) -c -o $(SERVER).o $(SERVER).cc

user.o: user.cc
	$(CC) $(VERSION) -c -o user.o user.cc

user_controller.o: user_controller.cc
	$(CC) $(VERSION) -c -o user_controller.o user_controller.cc

static_semaphore.o: $(SEMAPHORE).cc
	$(CC) $(VERSION) -c -o $(SEMAPHORE).o $(SEMAPHORE).cc


$(CLIENT): client.o
	$(CC) $(VERSION) -o $(CLIENT) client.o $(THREAD)


client.o: client.cc
	$(CC) $(VERSION) -c -o client.o client.cc


clean:
	rm *.o $(ALL)
