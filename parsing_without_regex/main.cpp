#include <iostream>
#include "buf_handler.h"
#include "zgml_manager.h"


int main(int argc, const char* argv[])
{
    InputBufHandler* buf_handler = InputBufHandler::instance();

    if (argc > 1) {
        buf_handler->redirectBuffer(argv[1]);
    } else {
        // buf_handler->redirectBuffer(zagrava::findZgmlFile()); 
    }

    int     nTags {0};
    int nRequests {0};
    std::cin >> nTags >> nRequests;

    zagrava::ZgmlManager zgml_parser(nTags);

    while (nRequests > 0) {
        std::cout << zgml_parser.getAttribute() << '\n';
        --nRequests;
    }

    // buf_handler->reset(); std::cin.get();
}

