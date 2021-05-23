#include "zgml_manager.h"

namespace zagrava {


ZgmlManager::ZgmlManager (int nTags)
{
    while (nTags-- > 0)
    { insertTag(); }
}
 

void ZgmlManager::insertTag ()
{
    std::ws(std::cin);
    while (std::cin.get() != '<') {
        if (std::cin.peek() == '\n')
        { return; }
    }

    std::string tag;
    std::getline(std::ws(std::cin), tag, '>');

    parseTag(tag);
}


std::string ZgmlManager::getAttribute ()
{
    std::string request;
    std::cin >> request;

    return findAttribute(toWords(request));
}


StringsVector
ZgmlManager::toWords (std::string_view request)
{
    StringsVector words; 
    auto delim_pos {std::string::npos};

    do {
        request.remove_prefix(delim_pos + 1U);

        delim_pos = request.find_first_of(".~");
        words.push_back(std::string(request.substr(0, delim_pos)));

    } while (delim_pos != std::string::npos);

    return words;
}


void ZgmlManager::parseTag (const std::string& tag)
{
    if (tag.front() == '/') {
        m_words.pop_back();
        return;
    }

    std::stringstream sstrm;
    std::transform(tag.begin(), tag.end(),
                   std::ostream_iterator<char> {sstrm},
                   [](char ch) {
                       return (ch == '=') ?  ' ' : ch;
                   });

    std::string attr_name, attr_key, attr_value;

    sstrm >> attr_name;
    m_words.push_back(attr_name);
    insertSubTree(m_words.begin(), m_words.end());

    while (sstrm >> attr_key >> std::quoted(attr_value))
    {
        if (attr_value.empty())
        { continue; }

        [this](auto ...attrs) {
            (m_words.emplace_back(attrs), ...);

            insertSubTree(m_words.begin(), m_words.end());
            m_words.resize(m_words.size() - sizeof...(attrs));

        } (attr_key, attr_value);
    }
}


} // namespace zagrava

