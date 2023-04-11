#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Xor : public AComponent
    {
    public:
        Xor(const std::string name, size_t IPin1 = 1, size_t IPin2 = 2, size_t OPin = 3);
        ~Xor() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}