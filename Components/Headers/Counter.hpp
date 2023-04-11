#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Counter : public AComponent
    {
    public:
        Counter(std::string const &name, size_t clock = 10, size_t reset = 11,
                size_t q0 = 9, size_t q1 = 7, size_t q2 = 6, size_t q3 = 5,
                size_t q4 = 3, size_t q5 = 2, size_t q6 = 4, size_t q7 = 13,
                size_t q8 = 12, size_t q9 = 14, size_t q10 = 15, size_t q11 = 1);
        ~Counter() = default;

        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin) override;
        std::string getType() const override;

    private:
        Tristate getValue(size_t pin);
        Tristate _last_clock_state;
        Tristate _last_reset_state;
        short _count;
    };
}