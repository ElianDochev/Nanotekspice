#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Input : public AComponent
    {
    public:
        Input(const std::string name, size_t OPin = 1);
        ~Input() = default;
        bool setStatus(nts::Tristate status) override;
        void simulate(std::size_t tick) override;
        std::string getType() const override;
        nts::Tristate compute(std::size_t pin) override;

    private:
        nts::Tristate _state;
        nts::Tristate _pending_state;
    };

}