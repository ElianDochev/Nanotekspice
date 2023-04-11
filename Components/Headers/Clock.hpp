#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Clock : public AComponent
    {
    public:
        Clock(const std::string name, size_t OPin = 1);
        ~Clock() = default;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;
        void simulate(std::size_t tick) override;
        bool setStatus(nts::Tristate status) override;

    private:
        nts::Tristate _state;
        bool _pending_state;
    };
}
