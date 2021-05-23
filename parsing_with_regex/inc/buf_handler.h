#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cerrno>
#include <regex>


namespace zagrava {

    std::string findZgmlFile();

} /* namespace zagrava */


class InputBufHandler
{
  private:
    std::streambuf* m_savingBuffer {std::cin.rdbuf()};
    std::ifstream   m_inputStream;

    InputBufHandler() = default;

  public:
    ~InputBufHandler();

    static InputBufHandler* instance();

    void reset();
    void redirectBuffer(std::string filename);
};

