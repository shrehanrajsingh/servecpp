#pragma once

#if !defined(HMACOS_TH_HPP)
#define HMACOS_TH_HPP

#include <thread>
#include <vector>
#include "server.hpp"

class Server_Mult: Server
{
    std::vector<std::thread> clients; // client threads

    static void _Handle_Read(Server_Mult *, int);
public:
    Server_Mult(): Server(8100) {}
    
    void listen();
    void accept();
    void read(int);
    void send(int, const String &);

    ~Server_Mult();
};

#endif

