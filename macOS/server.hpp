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
protected:
    int port;
    int fd;
    struct sockaddr_in address;
    Vector<int> nsocks;

    int _get_read_ns_buffer(int, char *);
    int _start_listen_routine();

public:
    Server();
    Server(int);
    
    virtual void listen();
    virtual void accept();
    
    virtual void read(int);
    virtual void send(int, const String &);

    ~Server();
};

class ServerCustom: public Server
{
public:
    ServerCustom(): Server(8000) {};

    void
    listen()
    {
        if (_start_listen_routine())
        {
            perror("listen failed");
            close(fd);
            exit(-1);
        }

        std::cout << "Custom server listening on port 8000\n";
    }

    void
    accept()
    {
        int addrlen = sizeof(address);
        int ns = ::accept(fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        
        if (ns < 0)
        {
            perror("accept failed");
            close(fd);
            exit(-1);
        }

        nsocks.push_back(ns);
        read(ns);
    }
    
    void
    read(int ns)
    {
        char buffer[1024];
        int br = 0;
    
        while ((br = _get_read_ns_buffer(ns, (char *)buffer)) > 0)
        {
            buffer[br] = '\0';
            send(
                ns,
                String(buffer)
            );
        }
    }

    void
    send(int ns, const String &resp)
    {
        char *rr = resp.to_string();
        ::send(ns, rr, strlen(rr), 0);
    }
};

#endif



