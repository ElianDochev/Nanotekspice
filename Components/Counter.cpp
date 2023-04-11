#include "Headers/Counter.hpp"

nts::Counter::Counter(std::string const &name, size_t clock, size_t reset,
                      size_t q0, size_t q1, size_t q2, size_t q3,
                      size_t q4, size_t q5, size_t q6, size_t q7,
                      size_t q8, size_t q9, size_t q10, size_t q11)
    : AComponent(name)
{
    pins_index[clock] = 10;
    pins_index[reset] = 11;
    pins_index[q0] = 9;
    pins_index[q1] = 7;
    pins_index[q2] = 6;
    pins_index[q3] = 5;
    pins_index[q4] = 3;
    pins_index[q5] = 2;
    pins_index[q6] = 4;
    pins_index[q7] = 13;
    pins_index[q8] = 12;
    pins_index[q9] = 14;
    pins_index[q10] = 15;
    pins_index[q11] = 1;

    input_pins[pins_index[clock]] = std::make_pair(nullptr, 0);
    input_pins[pins_index[reset]] = std::make_pair(nullptr, 0);
    output_pins[pins_index[q0]] = nullptr;
    output_pins[pins_index[q1]] = nullptr;
    output_pins[pins_index[q2]] = nullptr;
    output_pins[pins_index[q3]] = nullptr;
    output_pins[pins_index[q4]] = nullptr;
    output_pins[pins_index[q5]] = nullptr;
    output_pins[pins_index[q6]] = nullptr;
    output_pins[pins_index[q7]] = nullptr;
    output_pins[pins_index[q8]] = nullptr;
    output_pins[pins_index[q9]] = nullptr;
    output_pins[pins_index[q10]] = nullptr;
    output_pins[pins_index[q11]] = nullptr;

    _last_clock_state = Tristate::Undefined;
    _last_reset_state = Tristate::Undefined;
    _count = 0;
    _tick = 0;
}

std::string nts::Counter::getType() const
{
    return "Counter";
}

nts::Tristate nts::Counter::getValue(size_t pin)
{
    pin = pins_index[pin];

    if (_last_clock_state == Tristate::Undefined)
        return Tristate::Undefined;
    // pins in ascending order form lowest to highest
    if (pin == 9)
        return (_count & 1 << 0) ? Tristate::True : Tristate::False;
    if (pin == 7)
        return (_count & 1 << 1) ? Tristate::True : Tristate::False;
    if (pin == 6)
        return (_count & 1 << 2) ? Tristate::True : Tristate::False;
    if (pin == 5)
        return (_count & 1 << 3) ? Tristate::True : Tristate::False;
    if (pin == 3)
        return (_count & 1 << 4) ? Tristate::True : Tristate::False;
    if (pin == 2)
        return (_count & 1 << 5) ? Tristate::True : Tristate::False;
    if (pin == 4)
        return (_count & 1 << 6) ? Tristate::True : Tristate::False;
    if (pin == 13)
        return (_count & 1 << 7) ? Tristate::True : Tristate::False;
    if (pin == 12)
        return (_count & 1 << 8) ? Tristate::True : Tristate::False;
    if (pin == 14)
        return (_count & 1 << 9) ? Tristate::True : Tristate::False;
    if (pin == 15)
        return (_count & 1 << 10) ? Tristate::True : Tristate::False;
    if (pin == 1)
        return (_count & 1 << 11) ? Tristate::True : Tristate::False;
    return Tristate::Undefined;
}

void nts::Counter::simulate(std::size_t tick)
{
    if (_tick == tick)
        return;
    _tick = tick;
    Tristate clock = input_pins[pins_index[10]].first ? input_pins[pins_index[10]].first->compute(input_pins[pins_index[10]].second) : Tristate::Undefined;
    Tristate reset = input_pins[pins_index[11]].first ? input_pins[pins_index[11]].first->compute(input_pins[pins_index[11]].second) : Tristate::Undefined;

    if (clock == Tristate::Undefined || reset != _last_reset_state)
    {
        if (clock == Tristate::Undefined)
        {
            _last_clock_state = Tristate::Undefined;
            _last_reset_state = reset;
            return;
        }
        _count = 0;
        _last_reset_state = reset;
        return;
    }
    if (clock == _last_clock_state)
        return;
    _last_clock_state = clock;
    ++_count;
    if (_count > 4095)
        _count = 0;
}

nts::Tristate nts::Counter::compute(std::size_t pin)
{
    return getValue(pin);
}
