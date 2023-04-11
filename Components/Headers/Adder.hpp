#pragma once

#include "../Interface-Abstract/AComponent.hpp"

namespace nts
{
    class Adder : public AComponent
    {
    public:
        Adder(const std::string name, size_t carry = 9, size_t carryOut = 14,
              size_t b4 = 15, size_t a4 = 1, size_t b3 = 2, size_t a3 = 3,
              size_t b2 = 4, size_t a2 = 5, size_t b1 = 6, size_t a1 = 7,
              size_t out1 = 10, size_t out2 = 11, size_t out3 = 12, size_t out4 = 13);
        ~Adder() = default;

        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin) override;
        // void dump(std::string front) const override; // may not need to override
        std::string getType() const override;

    private:
        Tristate carry[5];
        bool _compiled;
        void compile();
    };
}
