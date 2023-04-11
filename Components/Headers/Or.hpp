#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Or : public AComponent
    {
    public:
        Or(const std::string name, size_t IPin1 = 1, size_t IPin2 = 2, size_t OPin = 3);
        ~Or() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}
