#include "static_semaphore.hpp"

scoped_sem_t::scoped_sem_t() {
        sem_init(&sem, 0, 1);
}

scoped_sem_t::~scoped_sem_t() {
        sem_destroy(&sem);
}

sem_t& scoped_sem_t::get() {
        return sem;
}

