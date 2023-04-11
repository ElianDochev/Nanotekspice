#include "Headers/True.hpp"

nts::TrueC::TrueC(const std::string name, size_t OPin) : AComponent(name)
{
    pins_index[1] = OPin;
    output_pins[OPin] = nullptr;
}

nts::Tristate nts::TrueC::compute(std::size_t pin)
{
    (void)pin;
    return nts::Tristate::True;
}

std::string nts::TrueC::getType() const
{
    return "True";
}