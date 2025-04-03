#if !defined(SERVER_H)

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#include "../rsstring.hpp"

#define DEFAULT_SERVER_PORT 9211

class Server
{
    int port;
    int fd;
    struct sockaddr_in address;
    Vector<int> nsocks;

    int _get_read_ns_buffer(int, char *);

public:
    Server();
    Server(int);
    
    void listen();
    void accept();
    
    virtual String read(int);
    virtual void send(int, const String &);

    ~Server();
};

#endif

