#include "Headers/False.hpp"

nts::FalseC::FalseC(const std::string name, size_t OPin) : AComponent(name)
{
    pins_index[1] = OPin;
    output_pins[OPin] = nullptr;
}

nts::Tristate nts::FalseC::compute(std::size_t pin)
{
    (void)pin;
    return nts::Tristate::False;
}

std::string nts::FalseC::getType() const
{
    return "False";
}