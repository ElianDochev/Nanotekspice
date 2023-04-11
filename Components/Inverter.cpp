#include "Headers/Inverter.hpp"

nts::Inverter::Inverter(const std::string name,
                        size_t Ipin1, size_t Opin1,
                        size_t Ipin2, size_t Opin2,
                        size_t Ipin3, size_t Opin3,
                        size_t Ipin4, size_t Opin4,
                        size_t Ipin5, size_t Opin5,
                        size_t Ipin6, size_t Opin6)
    : AComponent(name), _not_1("not_1", Ipin1, Opin1), _not_2("not_2", Ipin2, Opin2),
      _not_3("not_3", Ipin3, Opin3), _not_4("not_4", Ipin4, Opin4),
      _not_5("not_5", Ipin5, Opin5), _not_6("not_6", Ipin6, Opin6)
{
    pins_index[1] = Opin1;
    pins_index[2] = Opin2;
    pins_index[3] = Opin3;
    pins_index[4] = Opin4;
    pins_index[5] = Opin5;
    pins_index[6] = Opin6;
}

void nts::Inverter::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin == 1 || pin == 2)
    {
        _not_1.setLink(pin, other, otherPin);
    }
    else if (pin == 3 || pin == 4)
    {
        _not_2.setLink(pin, other, otherPin);
    }
    else if (pin == 5 || pin == 6)
    {
        _not_3.setLink(pin, other, otherPin);
    }
    else if (pin == 8 || pin == 9)
    {
        _not_4.setLink(pin, other, otherPin);
    }
    else if (pin == 10 || pin == 11)
    {
        _not_5.setLink(pin, other, otherPin);
    }
    else if (pin == 12 || pin == 13)
    {
        _not_6.setLink(pin, other, otherPin);
    }
}

nts::Tristate nts::Inverter::compute(std::size_t pin)
{
    if (pin == 1 || pin == 2)
    {
        return _not_1.compute(pin);
    }
    else if (pin == 3 || pin == 4)
    {
        return _not_2.compute(pin);
    }
    else if (pin == 5 || pin == 6)
    {
        return _not_3.compute(pin);
    }
    else if (pin == 8 || pin == 9)
    {
        return _not_4.compute(pin);
    }
    else if (pin == 10 || pin == 11)
    {
        return _not_5.compute(pin);
    }
    else if (pin == 12 || pin == 13)
    {
        return _not_6.compute(pin);
    }
    throw std::invalid_argument("Invalid pin when computing gate");
}

void nts::Inverter::dump(std::string front) const
{
    std::cout << front << name << " : Inverter" << std::endl;
    _not_1.dump(front + "\t");
    _not_2.dump(front + "\t");
    _not_3.dump(front + "\t");
    _not_4.dump(front + "\t");
    _not_5.dump(front + "\t");
    _not_6.dump(front + "\t");
}

int nts::Inverter::getPinType(std::size_t pin) const
{
    if (pin == 1 || pin == 2)
    {
        return _not_1.getPinType(pin);
    }
    else if (pin == 3 || pin == 4)
    {
        return _not_2.getPinType(pin);
    }
    else if (pin == 5 || pin == 6)
    {
        return _not_3.getPinType(pin);
    }
    else if (pin == 8 || pin == 9)
    {
        return _not_4.getPinType(pin);
    }
    else if (pin == 10 || pin == 11)
    {
        return _not_5.getPinType(pin);
    }
    else if (pin == 12 || pin == 13)
    {
        return _not_6.getPinType(pin);
    }
    return -1;
}

std::string nts::Inverter::getType() const
{
    return "Inverter";
}