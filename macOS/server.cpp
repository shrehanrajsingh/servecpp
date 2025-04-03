#include "server.hpp"

Server::Server() { Server(DEFAULT_SERVER_PORT); }

Server::Server(int _Port)
{
    port = _Port;
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (!fd)
    {
        perror("Socket failed");
        exit(-1);
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt failed");
        close(fd);
        exit(-1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(fd);
        exit(-1);
    }
}

int
Server::_get_read_ns_buffer(int ns, char *buf)
{
     return ::read(ns, buf, 1024 * sizeof(char));
}

int
Server::_start_listen_routine()
{
    return ::listen(fd, 3);
}

void
Server::listen()
{
    if (_start_listen_routine())
    {
        perror("listen failed");
        close(fd);
        exit(-1);
    }

    std::cout << "Server listening on port " << port << '\n';
    accept();
}

void
Server::accept()
{
    int addrlen = sizeof(address);
    int ns = ::accept(fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    if (ns < 0)
    {
        perror("Accept failed");
        close(fd);
        exit(-1);
    }

    nsocks.push_back(ns);

    read(ns);
}

void
Server::read(int ns)
{
    char buffer[1024];
    int br = 0;

    while ((br = _get_read_ns_buffer(ns, (char *)buffer)) > 0)
    {
        buffer[br - 1] = '\0';
        send(
            ns, 
            String("Received response \"") + ((char *)buffer)
            + "\" from client " + ns + '\n'
        );
    }
}

void
Server::send(int ns, const String &resp)
{
    char *rr = resp.to_string();
    ::send(ns, rr, strlen(rr), 0);
}

Server::~Server()
{
    close(fd);

    for (int i = 0; i < nsocks.get_size(); i++)
        close(nsocks[i]);        
}



