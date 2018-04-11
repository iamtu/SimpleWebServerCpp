// James Blades (BetaWar)
// dreamincode.net
#include "Thread.h"
#include <iostream>

void Thread::run(){
    while(!m_stoprequested){
        if(workBot->ceaseThread){
            stop(workBot->killThread);
            return;
        }
        try{
            workBot->tick();
        }
        catch(...){ // Some error occurred, let the bot try to repair itself.
            std::cout << "An error occurred - run()\n";
            workBot->tack();
        }
    }
}
Thread::Thread(Runnable* bot) : m_stoprequested(false), m_running(false){
    //  pthread_mutex_init(&m_mutex, NULL);
    workBot = bot;
    workBot->ceaseThread = workBot->killThread = false;
}
Thread::~Thread(){
    //  pthread_mutex_destroy(&m_mutex);
}
void Thread::start(){
    if(m_running){
        return;
    }
    m_running = true;
    pthread_create(&m_thread, NULL, Thread::start_thread, this);
}
void Thread::stop(bool kill){
    if(!m_running){
        return;
    }
    m_running = false;
    m_stoprequested = true;
    pthread_cancel(m_thread);
    pthread_join(m_thread, NULL);
    if(kill){
        delete this;
    }
}
