#include <main.hpp>

void 
test_f()
{
    std::cout << "VECTOR TEST --------\n";
    test::rsvector();

    std::cout << "STRING TEST --------\n";
    test::rsstring();
}

int 
main (int argc, const char *argv[]) 
{
    //test_f();
    Server s(8000);
    s.listen();
    s.accept();
}
