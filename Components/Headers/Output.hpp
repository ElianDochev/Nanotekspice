#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Output : public AComponent
    {
    public:
        Output(const std::string name, size_t IPin = 1);
        ~Output() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
    };
}