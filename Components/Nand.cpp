#include "Headers/Nand.hpp"

nts::Nand::Nand(const std::string name, size_t Ipin1, size_t Ipin2, size_t Opin)
    : AComponent(name)
{
    pins_index[1] = Ipin1;
    pins_index[2] = Ipin2;
    pins_index[3] = Opin;

    input_pins[Ipin1] = std::pair<std::shared_ptr<IComponent>, std::size_t>(nullptr, 0);
    input_pins[Ipin2] = std::pair<std::shared_ptr<IComponent>, std::size_t>(nullptr, 0);
    output_pins[Opin] = nullptr;
}

nts::Tristate nts::Nand::compute(std::size_t pin)
{
    (void)pin;
    Tristate pin1;
    Tristate pin2;

    pin1 = input_pins[pins_index[1]].first ? input_pins[pins_index[1]].first->compute(input_pins[pins_index[1]].second) : nts::Tristate::Undefined;
    pin2 = input_pins[pins_index[2]].first ? input_pins[pins_index[2]].first->compute(input_pins[pins_index[2]].second) : nts::Tristate::Undefined;
    return (!(pin1 & pin2));
}

std::string nts::Nand::getType() const
{
    return "Nand";
}