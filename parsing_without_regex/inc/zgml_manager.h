#pragma once

#include <string_view>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

#include "zgml_tags_tree.h"


namespace zagrava {

using StringsVector = std::vector<std::string>;


class ZgmlManager : private ZgmlTagsTree
{
  private:
    StringsVector m_words;

  public:
    explicit
    ZgmlManager(int nTags);
    ZgmlManager() = default;

    auto    insertTag() -> void;
    auto getAttribute() -> std::string;

  private:
    auto  toWords(std::string_view request)    -> StringsVector;
    auto parseTag(const std::string& open_tag) -> void;
};


} /* namespace zagrava */

