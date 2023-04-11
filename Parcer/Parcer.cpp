#include "Headers/Parcer.hpp"
#include <exception>

nts::Parcer::Parcer(std::string const &filepath) : file{filepath}
{
    lineState = State::DEFAULT;
}

void nts::Parcer::parse(Factory &factory)
{
    void (nts::Parcer::*stateFunc[2])(Factory &) = {&nts::Parcer::parseChipset, &nts::Parcer::parseLink};

    while (file.getline(true).first != false)
    {
        if (filterComments())
            continue;
        if (!ControlState())
            throw InvalidStateException{"EOF when control state is reached line: "};
        if (lineState == State::DEFAULT)
            throw InvalidStateException{"Invalid state should not be DEFAULT"};
        (this->*stateFunc[static_cast<int>(lineState)])(factory);
    }
    if (lineState != State::LINK)
        throw InvalidStateException{"File ended before .links: was found"};
}

bool nts::Parcer::filterComments()
{
    size_t pos = file.getline().second.find('#');

    if (pos != std::string::npos)
        file.getline().second.erase(pos);
    if (file.getline().second.empty())
    {
        return true;
    }
    if (file.getline().second.find_first_not_of(' ') == std::string::npos && file.getline().second.find_first_not_of('\t') == std::string::npos)
    {
        return true;
    }
    return false;
}

bool nts::Parcer::ControlState()
{
    if (file.getline().second.find(".chipsets:") != std::string::npos)
    {
        lineState = State::CHIPSET;
        if (file.nextLine() == false)
            return false;
    }
    else if (file.getline().second.find(".links:") != std::string::npos)
    {
        lineState = State::LINK;
        if (file.nextLine() == false)
            return false;
    }
    return true;
}

void nts::Parcer::parseChipset(Factory &factory)
{
    size_t pos;
    std::string work_str = file.getline().second;
    std::string name;
    std::string type;

    work_str = removeSpaceTabs(work_str);
    pos = work_str.find(' ');
    if (pos == std::string::npos)
        pos = work_str.find('\t');
    type = work_str.substr(0, pos);
    pos = work_str.find_first_not_of(' ', pos) != std::string::npos ? work_str.find_first_not_of(' ', pos) : 0;
    pos = work_str.find_first_not_of('\t', pos) != std::string::npos ? work_str.find_first_not_of('\t', pos) : pos;
    if (pos == std::string::npos)
        pos = work_str.find_first_not_of(' ', pos);
    name = work_str.substr(pos);
    factory.createComponent(name, type);
}

void nts::Parcer::parseLink(Factory &factory)
{
    std::string work_str = file.getline().second;
    std::string first_half;
    std::string second_half;
    size_t pos; // aux var
    std::shared_ptr<IComponent> first;
    size_t pin_first;
    std::shared_ptr<IComponent> second;
    size_t pin_second;

    work_str = removeSpaceTabs(work_str);
    pos = work_str.find(' ');
    if (pos == std::string::npos)
        pos = work_str.find('\t');
    first_half = work_str.substr(0, pos);
    second_half = work_str.substr(pos);
    first_half = removeSpaceTabs(first_half);
    second_half = removeSpaceTabs(second_half);
    pos = first_half.find(':');
    first = factory.getComponent(first_half.substr(0, pos));
    pin_first = std::stoi(first_half.substr(pos + 1));
    pos = second_half.find(':');
    second = factory.getComponent(second_half.substr(0, pos));
    pin_second = std::stoi(second_half.substr(pos + 1));
    first->setLink(pin_first, *second, pin_second);
    second->setLink(pin_second, *first, pin_first);
}

std::string nts::Parcer::removeSpaceTabs(std::string &str)
{
    std::string ret = str;
    size_t pos;

    pos = ret.find_first_not_of(' ');
    if (pos != std::string::npos)
        ret.erase(0, pos);
    pos = ret.find_first_not_of('\t');
    if (pos != std::string::npos)
        ret.erase(0, pos);
    pos = ret.find_last_not_of(' ');
    if (pos != std::string::npos)
        ret.erase(pos + 1);
    pos = ret.find_last_not_of('\t');
    if (pos != std::string::npos)
        ret.erase(pos + 1);
    return ret;
}
