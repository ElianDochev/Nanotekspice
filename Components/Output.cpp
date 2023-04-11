#include "Headers/Output.hpp"

nts::Output::Output(const std::string name, size_t IPin) : AComponent(name)
{
    pins_index[1] = IPin;
    input_pins[IPin] = std::pair<std::shared_ptr<IComponent>, std::size_t>(nullptr, 0);
}

nts::Tristate nts::Output::compute(std::size_t pin)
{
    if (pin == 50)
    {
        if (input_pins[pins_index[1]].first == nullptr)
            return nts::Tristate::Undefined;
        std::string type = input_pins[pins_index[1]].first->getType();
        if (type == "False" || type == "True")
            return input_pins[pins_index[1]].first->compute(input_pins[pins_index[1]].second);
        else
            return Tristate::Undefined;
    }
    Tristate pin1;

    pin1 = input_pins[pins_index[1]].first ? input_pins[pins_index[1]].first->compute(input_pins[pins_index[1]].second) : nts::Tristate::Undefined;
    return pin1;
}

std::string nts::Output::getType() const
{
    return "Output";
}
