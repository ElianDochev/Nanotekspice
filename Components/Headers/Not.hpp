#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Not : public AComponent
    {
    public:
        Not(const std::string name, size_t IPin = 1, size_t OPin = 2);
        ~Not() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}