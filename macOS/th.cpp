#include "th.hpp"

void
Server_Mult::listen()
{
    if (_start_listen_routine())
    {
        perror("listen failed");
        close(fd);
        exit(-1);
    }

    std::cout << "server listening on port 8100\n";
}

void
Server_Mult::accept()
{
    while (1)
    {
        int ns = _accept_routine();
    
        if (ns < 0)
        {
            perror("accept failed");
            close(fd);
            exit(-1);
        }
    
        clients.emplace_back(_Handle_Read, this, ns);
    }
}

void
Server_Mult::read(int ns)
{
    char buffer[1024];
    int br;

    while ((br = _get_read_ns_buffer(ns, (char *)buffer)) > 0)
    {
        buffer[br] = '\0';
        send(ns, String(buffer));
    }
}

void
Server_Mult::send(int ns, const String &resp)
{
    char *rr = resp.to_string();
    ::send(ns, rr, strlen(rr), 0);
    delete rr;
}

Server_Mult::~Server_Mult()
{
}

void
Server_Mult::_Handle_Read(Server_Mult *obj, int ns)
{
    char buffer[1024];
    int br;

    while ((br = obj->Server::_get_read_ns_buffer(ns, (char *)buffer)) > 0)
    {
        buffer[br] = '\0';
        obj->send(ns, String(buffer));
    }
}
