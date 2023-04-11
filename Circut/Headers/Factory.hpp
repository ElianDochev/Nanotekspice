#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <exception>
// components includes
#include "../../Components/Headers/Input.hpp"
#include "../../Components/Headers/Output.hpp"
#include "../../Components/Headers/True.hpp"
#include "../../Components/Headers/False.hpp"
#include "../../Components/Headers/And.hpp"
#include "../../Components/Headers/Or.hpp"
#include "../../Components/Headers/Xor.hpp"
#include "../../Components/Headers/Not.hpp"
#include "../../Components/Headers/Clock.hpp"
#include "../../Components/Headers/Nor.hpp"
#include "../../Components/Headers/Nand.hpp"
#include "../../Components/Headers/Inverter.hpp"
#include "../../Components/Headers/Adder.hpp"
#include "../../Components/Headers/Counter.hpp"
#include "../../Components/Headers/Gate.hpp"

namespace nts
{

    class Factory
    {
        using T_ptr = std::shared_ptr<nts::IComponent>;

    public:
        Factory();
        ~Factory();
        void createComponent(const std::string &name, const std::string &type);
        std::unordered_map<std::string, T_ptr> &getComponents() { return m_components; }
        std::map<std::string, T_ptr> &getOutputComponents() { return outputComponents; }
        std::map<std::string, T_ptr> &getInputComponents() { return inputComponents; }
        T_ptr getComponent(const std::string &name);
        T_ptr getInputComponent(const std::string &name);
        T_ptr getOutputComponent(const std::string &name);
        class ComponentAlreadyExists : public std::exception
        {
        public:
            ComponentAlreadyExists(const std::string &name) : m_name(name) {}
            const char *what() const noexcept override
            {
                return m_name.c_str();
            }

        private:
            std::string m_name;
        };
        class ComponentDoesNotExist : public std::exception
        {
        public:
            ComponentDoesNotExist(const std::string &name) : m_name(name) {}
            const char *what() const noexcept override
            {
                return m_name.c_str();
            }

        private:
            std::string m_name;
        };

    private:
        std::unordered_map<std::string, T_ptr> m_components;
        std::map<std::string, T_ptr> inputComponents;
        std::map<std::string, T_ptr> outputComponents;
        std::map<std::string, std::function<void(std::string name)>> ComponetCreator;
    };
}
