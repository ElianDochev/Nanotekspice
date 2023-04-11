#pragma once

#include <fstream>
#include <sstream>

class FileReader
{
public:
    FileReader(std::string const &filepath);
    FileReader(FileReader const &) = delete;
    FileReader(FileReader &&) = default;
    ~FileReader() = default;
    std::pair<bool, std::string &> getline(bool getNewLine = false);
    bool nextLine();
    void reset();
    class FileNotFoundException : public std::exception
    {
    public:
        FileNotFoundException(std::string const &filepath) : msg(filepath + ": Cannot open file.") {}
        ~FileNotFoundException() = default;
        char const *what() const noexcept override { return msg.c_str(); }

    private:
        std::string msg;
    };

private:
    std::string data;
    std::stringstream sstream;
    std::string line;
};
