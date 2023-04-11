#pragma once

#include "IComponent.hpp"
#include <map>
#include <utility>
#include <vector>
#include <memory>

namespace nts
{
    class AComponent : public IComponent
    {
    public:
        using I_ptr = std::shared_ptr<IComponent>;
        AComponent(std::string const &name) : name(name) {}
        virtual ~AComponent() = default;
        virtual Tristate compute(std::size_t pin) = 0;
        virtual void simulate(std::size_t tick) { (void)tick; };
        virtual void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
        // used by input and output components
        virtual bool setStatus(nts::Tristate status);
        // forgot what this is for
        virtual std::string getType() const = 0;
        // # utils
        // gets the type of the pin, 0 if input, 1 if output, -1 if invalid
        virtual void dump(std::string front = "") const;
        std::string getName() const;
        virtual int getPinType(std::size_t pin) const;
        class InvalidPinException : public std::exception
        {
        public:
            InvalidPinException(std::string const &message) : _message(message) {}
            virtual const char *what() const throw()
            {
                return _message.c_str();
            }

        private:
            std::string _message;
        };

    protected:
        std ::map<std::size_t, I_ptr> output_pins;
        std ::map<std::size_t, std::pair<I_ptr, std::size_t>> input_pins;
        std ::map<std::size_t, std::size_t> pins_index;
        std::string name;
        size_t _tick;
    };
};