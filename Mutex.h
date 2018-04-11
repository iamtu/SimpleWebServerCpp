// James Blades (BetaWar)
// dreamincode.net
#ifndef Mutex_H
#define Mutex_H

#include <map>
#include <pthread.h>

class Mutex{
private:
    typedef std::map<void*, pthread_mutex_t> items_t;
    static items_t& get_items(){
        static items_t* items = new items_t;
        return *items;
    }
public:
    static void lock(void* addr){
        items_t& items = get_items();
        if(&items[addr] == NULL){
            pthread_mutex_init(&items[addr], NULL);
        }
        pthread_mutex_lock(&items[addr]);
    }
    static void unlock(void* addr){
        items_t& items = get_items();
        pthread_mutex_unlock(&items[addr]);
    }
};

#endif
