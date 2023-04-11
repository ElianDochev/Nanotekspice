#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class And : public AComponent
    {
    public:
        And(const std::string name, size_t Ipin1 = 1, size_t Ipin2 = 2, size_t Opin = 3);
        ~And() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}