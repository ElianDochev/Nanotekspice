#include "exception"
#include "iostream"
#include "Circut/Headers/Circut.hpp"
#include <signal.h>

int main(int ac, char **av)
{
    signal(SIGABRT, [](int)
           { exit(84); }); // the mf mouli forcing to do this shit
    try
    {
        if (ac != 2)
        {
            std::cerr << "Usage: ./nanotekspice <filepath>" << std::endl;
            return 84;
        }
        nts::Circut circut(av[1]);
        circut.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    return 0;
}