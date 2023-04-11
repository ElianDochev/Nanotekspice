#include "Headers/Adder.hpp"
#include <algorithm>

nts::Adder::Adder(const std::string name, size_t carry, size_t carryOut,
                  size_t b4, size_t a4, size_t b3, size_t a3,
                  size_t b2, size_t a2, size_t b1, size_t a1,
                  size_t out1, size_t out2, size_t out3, size_t out4)
    : AComponent(name)
{
    _tick = 0;
    pins_index[9] = carry;
    pins_index[14] = carryOut;
    pins_index[15] = b4;
    pins_index[1] = a4;
    pins_index[2] = b3;
    pins_index[3] = a3;
    pins_index[4] = b2;
    pins_index[5] = a2;
    pins_index[6] = b1;
    pins_index[7] = a1;
    pins_index[10] = out1;
    pins_index[11] = out2;
    pins_index[12] = out3;
    pins_index[13] = out4;

    for (int i = 1; i < 8; ++i)
    {
        input_pins[pins_index[i]] = std::make_pair(nullptr, 0);
    }
    input_pins[pins_index[9]] = std::make_pair(nullptr, 0);
    input_pins[pins_index[15]] = std::make_pair(nullptr, 0);
    for (int i = 10; i < 15; ++i)
    {
        output_pins[pins_index[i]] = nullptr;
    }
    _compiled = false;
}

void nts::Adder::simulate(std::size_t tick)
{
    if (tick == _tick)
        return;
    _tick = tick;
    _compiled = false;
}

void nts::Adder::compile()
{
    auto res = adder(input_pins[pins_index[7]].first->compute(input_pins[pins_index[7]].second),
                     input_pins[pins_index[6]].first->compute(input_pins[pins_index[6]].second),
                     input_pins[pins_index[9]].first->compute(input_pins[pins_index[9]].second));
    carry[0] = res.first;
    auto rest = res.second;
    res = adder(input_pins[pins_index[5]].first->compute(input_pins[pins_index[5]].second),
                input_pins[pins_index[4]].first->compute(input_pins[pins_index[4]].second),
                rest);
    carry[1] = res.first;
    rest = res.second;
    res = adder(input_pins[pins_index[3]].first->compute(input_pins[pins_index[3]].second),
                input_pins[pins_index[2]].first->compute(input_pins[pins_index[2]].second),
                rest);
    carry[2] = res.first;
    rest = res.second;
    res = adder(input_pins[pins_index[1]].first->compute(input_pins[pins_index[1]].second),
                input_pins[pins_index[15]].first->compute(input_pins[pins_index[15]].second),
                rest);
    carry[3] = res.first;
    carry[4] = res.second;
    _compiled = true;
}

nts::Tristate nts::Adder::compute(std::size_t pin)
{
    if (output_pins.find(pin) == output_pins.end())
        throw InvalidPinException("Pin does not exist:" + std::to_string(pin));

    if (_compiled == false)
        compile();
    if (pins_index[10] == pin)
        return carry[0];
    if (pins_index[11] == pin)
        return carry[1];
    if (pins_index[12] == pin)
        return carry[2];
    if (pins_index[13] == pin)
        return carry[3];
    if (pins_index[14] == pin)
        return carry[4];
    return Tristate::Undefined;
}

std::string nts::Adder::getType() const
{
    return "Adder";
}