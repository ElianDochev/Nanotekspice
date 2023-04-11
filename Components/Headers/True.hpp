#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class TrueC : public AComponent
    {
    public:
        TrueC(const std::string name, size_t OPin = 1);
        ~TrueC() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}