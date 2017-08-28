#ifndef SERVER_CHAT_STATIC_SEMAPHORE_HPP
#define SERVER_CHAT_STATIC_SEMAPHORE_HPP

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

#endif
