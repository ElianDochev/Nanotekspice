#pragma once

#include "../../Parcer/Headers/Parcer.hpp"
#include "Factory.hpp"
#include <vector>

namespace nts
{
    class Circut
    {
    public:
        Circut(std::string const &filepath);
        ~Circut() = default;
        void run();

    private:
        Parcer parcer;
        Factory factory;
        std::vector<std::string> Outputs;            // outputs to display
        std::vector<std::string> Inputs;             // inputs to display
        std::vector<std::string> CommandInputBuffer; // buffer to store the inputs
        size_t tick;
        void simulate();
        void display();
        void dump();
        void loop();
        void input(std::string const &input);
    };
}