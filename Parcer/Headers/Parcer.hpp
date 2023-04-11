#pragma once

#include "../../Utils/Headers/FileReader.hpp"
#include "../../Circut/Headers/Factory.hpp"
namespace nts
{
    class Parcer
    {
    public:
        Parcer(std::string const &filepath);
        ~Parcer() = default;
        void parse(Factory &factory);
        static std::string removeSpaceTabs(std::string &str);
        class InvalidStateException : public std::exception
        {
        public:
            InvalidStateException(const std::string msg) : msg(msg) {}
            ~InvalidStateException() = default;
            char const *what() const noexcept override { return msg.c_str(); }

        private:
            std::string msg;
        };

    private:
        enum class State
        {
            CHIPSET,
            LINK,
            DEFAULT
        };
        State lineState;
        FileReader file;
        bool filterComments();
        bool ControlState();
        void parseChipset(Factory &factory);
        void parseLink(Factory &factory);
    };
}