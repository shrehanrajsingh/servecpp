#include <main.hpp>

void 
test_f()
{
    std::cout << "VECTOR TEST --------\n";
    test::rsvector();

    std::cout << "STRING TEST --------\n";
    test::rsstring();
}

void
test1()
{
    //test_f();
    ServerCustom s;
    s.listen();
    s.accept();
}

int 
main (int argc, const char *argv[]) 
{
    Server_Mult m;
    m.listen();
    m.accept();

    return 0;
}
