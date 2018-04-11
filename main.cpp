#include <iostream>
#include <list>
#include <string>
#include "Runnable.h"
#include "Socket.h"
#include "Thread.h"
#include "Mutex.h"
using namespace std;
class Listener: public Runnable{
private:
    Socket* client;
public:
    Listener(Socket* cli){
        client = cli;
    }
    ~Listener(){
        ceaseThread = true;
        delete client;
        killThread = true;
    }
    void tick(void){
        string in;
        if(!client->recv(in)){
            delete this;
        }
        if(!in.empty()){
            cout << in << endl;
            client->send("Hello Server\r\n");
            delete this;
        }
    }
    void tack(void){
        // does nothing.
    }
};
class Connector: public Runnable{
private:
    Socket* server;
public:
    Connector(Socket* s){
        server = s;
    }
    ~Connector(){
        ceaseThread = true;
        delete server;
        killThread = true;
    }
    void tick(void){
        Socket* client = new Socket();
        server->accept(*client);
        Runnable* listen = new Listener(client);
        Thread* listener = new Thread(listen);
        listener->start(); // at this point the server orphans the thread so it has to be able to clean up after itself.
    }
    void tack(void){
        // empty again
    }
};

int main(void){
    Socket* server = new Socket();
    if(!server->create()){
        cout << "Error – unable to create socket." << endl;
    }
    if(!server->bind(8080)){
        cout << "Error – unable to bind port 80, please make sure you are running the server as root." << endl;
    }
    if(!server->listen()){
        cout << "Error – unable to listen." << endl;
    }
    Runnable* serverListener = new Connector(server);
    Thread listenerThread(serverListener);
    listenerThread.start();
    while(1){
        // keep the program up and running
    }
    return 0;
}
