#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class FalseC : public AComponent
    {
    public:
        FalseC(const std::string name, size_t OPin = 1);
        ~FalseC() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}
