#pragma once

#include "Not.hpp"
#include <functional>

namespace nts
{
    class Inverter : public AComponent
    {
    public:
        Inverter(const std::string name, size_t Ipin1 = 1, size_t Opin1 = 2,
                 size_t Ipin2 = 3, size_t Opin2 = 4, size_t Ipin3 = 5,
                 size_t Opin3 = 6, size_t Ipin4 = 9, size_t Opin4 = 8,
                 size_t Ipin5 = 11, size_t Opin5 = 10, size_t Ipin6 = 13,
                 size_t Opin6 = 12);
        std::string getType() const override;
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;
        void dump(std::string front = "") const override;
        int getPinType(std::size_t pin) const override;
        nts::Tristate compute(std::size_t pin) override;
        ~Inverter() = default;

    private:
        Not _not_1;
        Not _not_2;
        Not _not_3;
        Not _not_4;
        Not _not_5;
        Not _not_6;
    };
}