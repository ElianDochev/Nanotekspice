#include "./Headers/Factory.hpp"
#include <memory>

nts::Factory::Factory()
{
    ComponetCreator["clock"] = [&](std::string name)
    {
        auto clock = std::make_shared<Clock>(name);
        m_components[name] = clock;
        inputComponents[name] = clock;
    };
    ComponetCreator["false"] = [&](std::string name)
    { m_components[name] = std::make_shared<FalseC>(name); };
    ComponetCreator["input"] = [&](std::string name)
    {
        std::shared_ptr<nts::IComponent> input = std::make_shared<Input>(name);
        m_components[name] = input;
        inputComponents[name] = input;
    };
    ComponetCreator["output"] = [&](std::string name)
    {
        std::shared_ptr<nts::IComponent> output = std::make_shared<Output>(name);
        m_components[name] = output;
        outputComponents[name] = output;
    };
    ComponetCreator["true"] = [&](std::string name)
    { m_components[name] = std::make_shared<TrueC>(name); };
    ComponetCreator["and"] = [&](std::string name)
    { m_components[name] = std::make_shared<And>(name); };
    ComponetCreator["or"] = [&](std::string name)
    { m_components[name] = std::make_shared<Or>(name); };
    ComponetCreator["xor"] = [&](std::string name)
    { m_components[name] = std::make_shared<Xor>(name); };
    ComponetCreator["not"] = [&](std::string name)
    { m_components[name] = std::make_shared<Not>(name); };
    ComponetCreator["nor"] = [&](std::string name)
    { m_components[name] = std::make_shared<Nor>(name); };
    ComponetCreator["nand"] = [&](std::string name)
    { m_components[name] = std::make_shared<Nand>(name); };
    ComponetCreator["4069"] = [&](std::string name)
    { m_components[name] = std::make_shared<Inverter>(name); };
    ComponetCreator["4081"] = [&](std::string name)
    { m_components[name] = std::make_shared<Gate<And>>(name, "AndGate"); };
    ComponetCreator["4071"] = [&](std::string name)
    { m_components[name] = std::make_shared<Gate<Or>>(name, "OrGate"); };
    ComponetCreator["4001"] = [&](std::string name)
    { m_components[name] = std::make_shared<Gate<Nor>>(name, "NorGate"); };
    ComponetCreator["4011"] = [&](std::string name)
    { m_components[name] = std::make_shared<Gate<Nand>>(name, "NandGate"); };
    ComponetCreator["4030"] = [&](std::string name)
    { m_components[name] = std::make_shared<Gate<Xor>>(name, "XorGate"); };
    ComponetCreator["4008"] = [&](std::string name)
    { m_components[name] = std::make_shared<Adder>(name); };
    ComponetCreator["4040"] = [&](std::string name)
    { m_components[name] = std::make_shared<Counter>(name); };
}

nts::Factory::~Factory() {}

void nts::Factory::createComponent(const std::string &name, const std::string &type)
{
    if (m_components.find(name) != m_components.end())
        throw ComponentAlreadyExists(name);
    if (ComponetCreator.find(type) == ComponetCreator.end())
        throw ComponentDoesNotExist("Component type doesnt exist: " + type);
    ComponetCreator[type](name);
}

std::shared_ptr<nts::IComponent> nts::Factory::getComponent(const std::string &name)
{
    if (m_components.find(name) == m_components.end())
        throw ComponentDoesNotExist("the component with this name doesnt exist: " + name);
    std::shared_ptr<nts::IComponent> component = m_components[name];
    return component;
}

std::shared_ptr<nts::IComponent> nts::Factory::getInputComponent(const std::string &name)
{
    if (inputComponents.find(name) == inputComponents.end())
        throw ComponentDoesNotExist(name);
    std::shared_ptr<nts::IComponent> component = inputComponents[name];
    return component;
}

std::shared_ptr<nts::IComponent> nts::Factory::getOutputComponent(const std::string &name)
{
    if (outputComponents.find(name) == outputComponents.end())
        throw ComponentDoesNotExist(name);
    std::shared_ptr<nts::IComponent> component = outputComponents[name];
    return component;
}
