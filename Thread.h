// James Blades (BetaWar)
// dreamincode.net
#ifndef THREAD_H
#define	THREAD_H

#include "Runnable.h"
#include <pthread.h>

class Thread{
private:
    volatile bool m_stoprequested;
    volatile bool m_running;
    pthread_t m_thread;
    Runnable* workBot;
    static void* start_thread(void* obj){
        ((Thread*)obj)->run();
        return NULL;
    }
    void run();
public:
    Thread(Runnable* bot);
    ~Thread();
    void start();
    void stop(bool kill);
};
#endif	/* THREAD_H */
