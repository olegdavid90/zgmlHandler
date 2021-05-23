#pragma once

#include <map>
#include <exception>

namespace zagrava {

static const char* kWarning {"Not Found!"};


class ZgmlTagsTree
{
  private:
    std::map<std::string, ZgmlTagsTree> m_storage;

  protected:
    template <typename InputIt>
    void insertSubTree (InputIt itr, InputIt end_itr)
    {
        if (itr == end_itr) {
            m_storage[kWarning];
            return;
        }

        m_storage[*itr].insertSubTree(std::next(itr), end_itr);
    }


    template <typename InputIt>
    std::string findAttribute (InputIt itr, InputIt end_itr) const
    {
        if (itr != end_itr) {
            try {
                const ZgmlTagsTree& subTree = m_storage.at(*itr);
                return subTree.findAttribute(std::next(itr), end_itr);
            } catch (const std::out_of_range&) {
                return kWarning;
            }
        }

        if (m_storage.size() == 1)
        { return m_storage.begin()->first; }

        return kWarning;
    }


    template <typename Container>
    std::string findAttribute (const Container& container) const
    {
        return findAttribute(container.cbegin(), container.cend());
    }
};


} /* namespace zagrava */

