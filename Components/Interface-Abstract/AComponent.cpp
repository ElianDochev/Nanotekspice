#include "AComponent.hpp"

void nts::AComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (getPinType(pin) == -1 || other.getPinType(otherPin) == -1)
        throw InvalidPinException("Pin does not exist:" + std::to_string(pin) + " or " + std::to_string(otherPin));
    if (getPinType(pin) == other.getPinType(otherPin))
        throw InvalidPinException("Cannot link two pins of the same type" + std::to_string(pin) + " and " + std::to_string(otherPin) + " are both " + (getPinType(pin) == 0 ? "input" : "output") + " pins of " + getName() + " and " + other.getName());
    if (getPinType(pin) == 0)
    {
        if (input_pins[pin].first != nullptr)
            throw InvalidPinException("Pin already linked");
        input_pins[pin] = std::make_pair(std::shared_ptr<IComponent>(&other), otherPin);
    }
    else
    {
        if (output_pins[pin] != nullptr)
            throw InvalidPinException("Pin already linked");
        output_pins[pin] = std::shared_ptr<IComponent>(&other);
    }
}

bool nts::AComponent::setStatus(nts::Tristate status)
{
    (void)status;
    return false;
}

int nts::AComponent::getPinType(std::size_t pin) const
{
    if (input_pins.find(pin) != input_pins.end())
        return 0;
    if (output_pins.find(pin) != output_pins.end())
        return 1;
    return -1;
}

void nts::AComponent::dump(std::string front) const
{
    std::cout << front << getName() << " : " << getType() << ":" << std::endl;
    if (input_pins.size() > 0)
        std::cout << front << "\tInput pins:" << std::endl;
    for (auto &pin : input_pins)
        std::cout << front << "\t\tPin " << pin.first << " : " << (pin.second.first ? (pin.second.first)->getName() : "undefined") << std::endl;
    if (output_pins.size() > 0)
        std::cout << front << "\tOutput pins:" << std::endl;
    for (auto &pin : output_pins)
        std::cout << front << "\t\tPin " << pin.first << " : " << (pin.second ? (pin.second)->getName() : "undefined") << std::endl;
}

std::string nts::AComponent::getName() const
{
    return name;
}
