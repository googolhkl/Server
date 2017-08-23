CC = g++

client: client.o account_manager.o
	$(CC) -o client client.o account_manager.o

client.o: client.cc
	$(CC) -std=c++11 -c client.cc

account_manager.o: account_manager.cc
	$(CC) -std=c++11 -c account_manager.cc

clean:
	rm *.o client
