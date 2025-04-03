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
    ServerCustom s;
    s.listen();
    s.accept();
}
