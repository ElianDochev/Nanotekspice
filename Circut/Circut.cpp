#include "Headers/Circut.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include <cstdlib>

bool run_loop = true; // global variable to stop the loop command

nts::Circut::Circut(std::string const &filepath) : parcer(filepath), factory(), tick(0) {}

void nts::Circut::run()
{
    std::string input;

    parcer.parse(factory);
    while (true)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, input))
        {
            if (std::cin.eof())
            {
                exit(0);
            }
        }
        input = Parcer::removeSpaceTabs(input);
        if (input == "exit")
            exit(0);
        else if (input == "simulate")
            simulate();
        else if (input == "display")
            display();
        else if (input == "dump")
            dump();
        else if (input == "clear")
            system("clear");
        else if (input == "loop")
            loop();
        else if (input.find('=') != std::string::npos)
            CommandInputBuffer.push_back(input);
        else
            std::cout << "Invalid command" << std::endl;
    }
}

void nts::Circut::simulate()
{
    Outputs.clear();
    Inputs.clear();
    tick++;
    if (CommandInputBuffer.size() > 0)
    {
        for (auto &input : CommandInputBuffer)
        {
            this->input(input);
        }
        CommandInputBuffer.clear();
    }
    for (auto &component : factory.getInputComponents())
    {
        component.second->simulate(tick);
    }

    for (auto &component : factory.getComponents())
    {
        component.second->simulate(tick);
    }
    for (auto &component : factory.getInputComponents())
    {
        Inputs.push_back(component.first + ": " + nts::ConvertTristate(component.second->compute(1)));
    }
    for (auto &component : factory.getOutputComponents())
    {
        Outputs.push_back(component.first + ": " + nts::ConvertTristate(component.second->compute(1)));
    }
}

void nts::Circut::display()
{
    if (tick == 0)
    {
        Outputs.clear();
        Inputs.clear();
        for (auto &component : factory.getOutputComponents())
        {
            Outputs.push_back(component.first + ": " + nts::ConvertTristate(component.second->compute(50)));
        }
        for (auto &component : factory.getInputComponents())
        {
            Inputs.push_back(component.first + ": " + nts::ConvertTristate(component.second->compute(1)));
        }
    }
    std::cout << "tick: " << tick << std::endl;
    std::cout << "input(s):" << std::endl;
    for (auto &input : Inputs)
        std::cout << "  " << input << std::endl;
    std::cout << "output(s):" << std::endl;
    for (auto &output : Outputs)
        std::cout << "  " << output << std::endl;
}

void nts::Circut::dump()
{
    std::cout << "dump :" << std::endl;
    auto components = factory.getComponents();

    for (auto &component : components)
        component.second->dump();
}

void nts::Circut::loop()
{

    signal(SIGINT, [](int)
           { run_loop = false; });
    while (run_loop)
    {
        simulate();
        display();
        usleep(100000);
    }
    signal(SIGINT, SIG_DFL);
    run_loop = true;
    std::cout << std::endl;
}

void nts::Circut::input(std::string const &input)
{
    std::string name;
    std::string tmp;
    int value;
    nts::Tristate state;
    std::shared_ptr<nts::IComponent> inputC; // input component
    size_t pos = input.find('=');

    name = input.substr(0, pos);
    name = Parcer::removeSpaceTabs(name);
    tmp = input.substr(pos + 1);
    try
    {
        value = std::stoi(Parcer::removeSpaceTabs(tmp));
        if (value == 0)
            state = nts::Tristate::False;
        else if (value >= 1)
            state = nts::Tristate::True;
        else
            state = nts::Tristate::Undefined;
    }
    catch (std::invalid_argument &e)
    {
        if (tmp == "U")
            state = nts::Tristate::Undefined;
        else
        {
            std::cerr << "Error: " << tmp << " is not a valid value" << std::endl;
            return;
        }
    }
    try
    {
        inputC = factory.getInputComponent(name);
        if (!inputC->setStatus(state)) // not needed because the list contains only inputs but just in case
        {
            std::cerr << "Error: " << name << " is not a configariable input component" << std::endl;
            return;
        }
    }
    catch (nts::Factory::ComponentDoesNotExist &e)
    {
        std::cerr << "Error: Component " << e.what() << "not declared" << std::endl;
        return;
    }
}
