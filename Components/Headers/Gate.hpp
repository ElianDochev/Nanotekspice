#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    template <typename T>
    class Gate : public AComponent
    {
    public:
        Gate(std::string const &name, std::string const &type,
             size_t Ipin1 = 1, size_t Ipin2 = 2, size_t Opin1 = 3,
             size_t Opin2 = 4, size_t Ipin3 = 5, size_t Ipin4 = 6,
             size_t Opin3 = 10, size_t Ipin5 = 8, size_t Ipin6 = 9,
             size_t Opin4 = 11, size_t Ipin7 = 12, size_t Ipin8 = 13)
            : AComponent(name), _type(type),
              _comp_1("comp_1", Ipin1, Ipin2, Opin1), _comp_2("comp_2", Ipin3, Ipin4, Opin2),
              _comp_3("comp_3", Ipin5, Ipin6, Opin3), _comp_4("comp_4", Ipin7, Ipin8, Opin4)
        {
            pins_index[1] = Opin1;
            pins_index[2] = Opin2;
            pins_index[3] = Opin3;
            pins_index[4] = Opin4;
        }
        std::string getType() const override
        {
            return _type;
        }
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override
        {
            if (pin == 1 || pin == 2 || pin == 3)
                _comp_1.setLink(pin, other, otherPin);
            else if (pin == 4 || pin == 5 || pin == 6)
                _comp_2.setLink(pin, other, otherPin);
            else if (pin == 8 || pin == 9 || pin == 10)
                _comp_3.setLink(pin, other, otherPin);
            else if (pin == 11 || pin == 12 || pin == 13)
                _comp_4.setLink(pin, other, otherPin);
            else
                throw std::invalid_argument("Invalid pin when linking gate");
        }
        void dump(std::string front = "") const override
        {
            std::cout << front << name << " : XorGate" << std::endl;
            auto functions = std::array<std::function<void()>, 4>();
            functions[0] = [&]()
            { _comp_1.dump("\t"); };
            functions[1] = [&]()
            { _comp_2.dump("\t"); };
            functions[2] = [&]()
            { _comp_3.dump("\t"); };
            functions[3] = [&]()
            { _comp_4.dump("\t"); };

            for (auto &function : functions)
            {
                std::cout << front;
                function();
            }
        }
        int getPinType(std::size_t pin) const override
        {
            if (pin == 1 || pin == 2 || pin == 3)
                return _comp_1.getPinType(pin);
            else if (pin == 4 || pin == 5 || pin == 6)
                return _comp_2.getPinType(pin);
            else if (pin == 8 || pin == 9 || pin == 10)
                return _comp_3.getPinType(pin);
            else if (pin == 11 || pin == 12 || pin == 13)
                return _comp_4.getPinType(pin);
            else
                throw std::invalid_argument("Invalid pin when computing gate");
        }
        nts::Tristate compute(std::size_t pin) override
        {
            if (pin == 1 || pin == 2 || pin == 3)
                return _comp_1.compute(pin);
            else if (pin == 4 || pin == 5 || pin == 6)
                return _comp_2.compute(pin);
            else if (pin == 8 || pin == 9 || pin == 10)
                return _comp_3.compute(pin);
            else if (pin == 11 || pin == 12 || pin == 13)
                return _comp_4.compute(pin);
            else
                throw std::invalid_argument("Invalid pin when computing gate");
        }
        ~Gate() = default;

    private:
        std::string _type;
        T _comp_1;
        T _comp_2;
        T _comp_3;
        T _comp_4;
    };
};
