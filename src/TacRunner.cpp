/* 
    Entry point for the Tac Runner app. This app 
    expects the following arguments in the given order:
    Arguments:
        filename : str = Name of the file to be run
*/

// C++ includes
#include <iostream>
#include <vector>

// Local includes
#include "Application.hpp"

int main(int argc, char *argv[])
{
    std::vector<std::string> args;
    // create arg vector
    for(int i=0; i < argc; i++)
        args.push_back(argv[i]);

    try
    {
        TacRunner::App app = TacRunner::App::from_arg_list(args);
        auto result = app.run();
        if (result == FAIL)
            std::cerr << "Failed execution" << std::endl;
    }
    catch (char const * msg) // constant string
    {
        std::cerr << msg << std::endl;
    }

    return 0;
}
