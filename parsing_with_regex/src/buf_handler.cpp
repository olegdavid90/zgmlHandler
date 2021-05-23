#include "buf_handler.h"

namespace zagrava {

namespace fs = std::filesystem;

std::string findZgmlFile ()
{
    std::string filename;
    unsigned nFiles {0};

    const std::regex extension(".+\\.zgml$",
                               std::regex_constants::icase);

    for (const auto& entry :
            fs::directory_iterator(fs::current_path())) {

        if (fs::is_regular_file(fs::status(entry))) {

            if (std::regex_match(entry.path().string(), extension))
            {
                ++nFiles;
                filename = entry.path().string();
            }
        }
    }

    if (nFiles == 1)
    { return filename; }

    return {};
}

} /* namespace zagrava */


InputBufHandler* InputBufHandler::instance ()
{
    static InputBufHandler inst {};
    return &inst;
}


void InputBufHandler::reset ()
{
    m_inputStream.close();
    std::cin.rdbuf(m_savingBuffer);
}


void
InputBufHandler::redirectBuffer (std::string filename)
{
    if (filename.empty())
    { return; }

    reset();
    m_inputStream.open(filename);

    if (!m_inputStream.is_open()) {
        std::cerr << std::quoted(filename)
                  << ": no such file in the directory\n";
        std::exit(errno);
    }

    std::cin.rdbuf(m_inputStream.rdbuf());
}


InputBufHandler::~InputBufHandler ()
{ reset(); }


