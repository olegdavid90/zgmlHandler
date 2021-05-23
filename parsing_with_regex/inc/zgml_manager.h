#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <regex>


namespace zagrava {


class ZgmlManager : private std::string
{
  public:
    explicit
    ZgmlManager(int nTags);
    ZgmlManager() = default;

    auto getAttribute() const -> std::string;
    auto    insertTag()       -> void;
};


} /* namespace zagrava */


