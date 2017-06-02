CC = g++
TEST_PATH = /home/ubuntu/googletest
LIB = -lgtest -lgmock
DEPENDENCY_O = test.o rand.o time.o

VERSION = -std=c++11

test: $(DEPENDENCY_O)
	$(CC) $(VERSION) -o test $(DEPENDENCY_O) -L$(TEST_PATH)/lib $(LIB) -pthread

test.o: test.cc
	$(CC) $(VERSION) -pthread -I$(TEST_PATH)/include -c -o test.o test.cc 

rand.o: rand.cc
	$(CC) $(VERSION) -c -o rand.o rand.cc

time.o: time.cc
	$(CC) $(VERSION) -c -o time.o time.cc

clean:
	rm *.o test
