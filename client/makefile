CC = g++

client: client.o game_manager.o
	$(CC) -o client client.o game_manager.o

client.o: client.cc
	$(CC) -std=c++11 -c client.cc

game_manager.o: game_manager.cc
	$(CC) -std=c++11 -c game_manager.cc

clean:
	rm *.o client
