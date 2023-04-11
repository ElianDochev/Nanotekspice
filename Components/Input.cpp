#include "Headers/Input.hpp"

nts::Input::Input(const std::string name, size_t OPin) : AComponent(name)
{
    pins_index[1] = OPin;
    output_pins[OPin] = nullptr;
    _state = nts::Tristate::Undefined;
    _pending_state = nts::Tristate::Undefined;
    _tick = 0;
}

void nts::Input::simulate(std::size_t tick)
{
    if (tick == _tick)
        return;
    _tick = tick;
    _state = _pending_state;
}

nts::Tristate nts::Input::compute(std::size_t pin)
{
    (void)pin;
    return _state;
}

std::string nts::Input::getType() const
{
    return "Input";
}

bool nts::Input::setStatus(nts::Tristate status)
{
    _pending_state = status;
    return true;
}
