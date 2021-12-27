/* 
    Entry point for the Tac Runner app. This app 
    expects the following arguments in the given order:
    Arguments:
        filename : str = Name of the file to be run
*/

// C++ includes
#include <iostream>

// Local includes
#include "Lexer.hpp" // note that this include should be before Parser.hpp
#include "_Parser.hpp"
#include "TacReader.hpp"

using namespace TacRunner;

int main(int argc, char *argv[])
{
    TacReader interpreter;
    interpreter.parse("test_files/data_section.txt");
    std::cout << interpreter.str() << std::endl;
    return 0;
}