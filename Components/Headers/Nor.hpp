#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Nor : public AComponent
    {
    public:
        Nor(const std::string name, size_t IPin1 = 1, size_t IPin2 = 2, size_t OPin = 3);
        ~Nor() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}
