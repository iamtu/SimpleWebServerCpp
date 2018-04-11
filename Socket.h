// James Blades (BetaWar)
// dreamincode.net
// Definition of the Socket class
#ifndef Socket_class
#define Socket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;
//const int MSG_NOSIGNAL = 0; // defined by dgame

class Socket{
private:
    int m_sock;
    sockaddr_in m_addr;
public:
    Socket();
    virtual ~Socket();
    // Server initialization
    bool create();
    bool bind(const int port);
    bool listen(void) const;
    bool listen(const int connections) const;
    bool accept(Socket&) const;
    // Client initialization
    bool connect(const std::string hostname, const int port);
    std::string getIP() const;
    unsigned short getPort() const;
    // Data Transimission
    bool send(const std::string) const;
    int recv(std::string&) const;

    void set_non_blocking(const bool);
    bool is_valid() const;
};
#endif
