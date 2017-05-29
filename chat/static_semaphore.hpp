//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <arpa/inet.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <netinet/in.h>
#include <semaphore.h>

#include <iostream>

class scoped_sem_t {
private:
        sem_t sem;

public:
        scoped_sem_t();
        ~scoped_sem_t();

        sem_t& get();
};

