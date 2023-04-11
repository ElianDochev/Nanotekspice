#pragma once

#include <iostream>
#include "../../Utils/Headers/Opps.hpp"

namespace nts
{
    enum class Tristate
    {
        Undefined = (-true),
        True = true,
        False = false
    };
    class IComponent
    {
    public:
        virtual ~IComponent() = default;
        virtual nts::Tristate compute(std ::size_t pin) = 0;
        virtual void setLink(std ::size_t pin, nts ::IComponent &other, std ::size_t otherPin) = 0;
        virtual bool setStatus(nts::Tristate status) = 0;
        virtual void simulate(std::size_t tick) = 0;
        // utils
        virtual int getPinType(std ::size_t pin) const = 0; // returns 0 if pin is an input, 1 if pin is an output, -1 if pin is invalid
        virtual std::string getName() const = 0;
        // bedug function
        virtual std::string getType() const = 0;
        virtual void dump(std::string front = "") const = 0; // prints the component type and the state of each pin
    };
};
