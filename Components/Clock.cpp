#include "./Headers/Clock.hpp"

nts::Clock::Clock(const std::string name, size_t OPin) : AComponent(name)
{
    pins_index[1] = OPin;
    output_pins[OPin] = nullptr;
    _state = nts::Tristate::Undefined;
    _tick = 0;
    _pending_state = false;
}

void nts::Clock::simulate(std::size_t tick)
{
    if (tick == _tick)
        return;
    _tick = tick;
    if (_pending_state)
    {
        _pending_state = false;
        return;
    }
    _state = !_state;
}

nts::Tristate nts::Clock::compute(std::size_t pin)
{
    (void)pin;
    return _state;
}

bool nts::Clock::setStatus(nts::Tristate status)
{
    _state = status;
    _pending_state = true;
    return true;
}

std::string nts::Clock::getType() const
{
    return "Clock";
}
