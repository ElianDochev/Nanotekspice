#include "Headers/Not.hpp"

nts::Not::Not(const std::string name, size_t IPin, size_t OPin)
    : AComponent(name)
{
    pins_index[1] = IPin;
    pins_index[2] = OPin;

    input_pins[IPin] = std::pair<std::shared_ptr<IComponent>, std::size_t>(nullptr, 0);
    output_pins[OPin] = nullptr;
}

nts::Tristate nts::Not::compute(std::size_t pin)
{
    (void)pin;
    Tristate state = input_pins[pins_index[1]].first ? input_pins[pins_index[1]].first->compute(input_pins[pins_index[1]].second) : Tristate::Undefined;

    return (!state);
}

std::string nts::Not::getType() const
{
    return "Not";
}
