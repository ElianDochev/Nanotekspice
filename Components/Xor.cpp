#include "Headers/Xor.hpp"

nts::Xor::Xor(const std::string name, size_t IPin1, size_t IPin2, size_t OPin)
    : AComponent(name)
{
    pins_index[1] = IPin1;
    pins_index[2] = IPin2;
    pins_index[3] = OPin;

    input_pins[IPin1] = std::pair<std::shared_ptr<IComponent>, std::size_t>(nullptr, 0);
    input_pins[IPin2] = std::pair<std::shared_ptr<IComponent>, std::size_t>(nullptr, 0);
    output_pins[OPin] = nullptr;
}

nts::Tristate nts::Xor::compute(std::size_t pin)
{
    (void)pin;
    Tristate state1;
    Tristate state2;

    state1 = input_pins[pins_index[1]].first ? input_pins[pins_index[1]].first->compute(input_pins[pins_index[1]].second) : nts::Tristate::Undefined;
    state2 = input_pins[pins_index[2]].first ? input_pins[pins_index[2]].first->compute(input_pins[pins_index[2]].second) : nts::Tristate::Undefined;

    return (state1 ^ state2);
}

std::string nts::Xor::getType() const
{
    return "Xor";
}