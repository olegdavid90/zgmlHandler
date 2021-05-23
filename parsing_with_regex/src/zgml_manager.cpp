#include "zgml_manager.h"

namespace zagrava {

static const char* kWarning {"Not Found!"};
    

ZgmlManager::ZgmlManager (int nTags)
{
    while (nTags-- > 0)
    { insertTag(); }
}


void ZgmlManager::insertTag ()
{
    std::string tag;
    std::getline(std::ws(std::cin), tag);

    this->append(tag);
}


std::string ZgmlManager::getAttribute () const
{
    std::string request;
    std::cin >> request;

    auto tag_begin = this->cbegin();
    auto tag_end   = this->cend();

    std::smatch match_result;

    while (std::regex_search(request, match_result,
                             std::regex("(.+?)[~\\.]")))
    {
        std::ostringstream osstrm;
        osstrm << "<\\s*(" << match_result.str(1) << "\\b)"
                  "(.*?)" "<\\s*/\\s*(\\1)\\s*>";

        request = match_result.suffix();

        if (std::regex_search(tag_begin, tag_end,
                              match_result,
                              std::regex(osstrm.str())))
        {
            tag_begin = match_result[2].first;
            tag_end   = match_result[2].second;
            continue;
        }
        
        return kWarning;
    }

    std::ostringstream osstrm;
    osstrm << "\\b" << request << "\\s*=\\s*\"([^\"]+)";

    if (std::regex_search(tag_begin, tag_end,
                          match_result,
                          std::regex(osstrm.str())))  {

        return match_result.str(1);
    }

    return kWarning;
}


} /* namespace zagrava */

