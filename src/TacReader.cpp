
// Local includes
#include "TacReader.hpp"
#include "Tac.hpp"

// C++ Includes
#include <sstream>
#include <fstream>

using namespace TacRunner;

TacReader::TacReader() :
    m_instructions(),
    m_scanner(*this),
    m_parser(m_scanner, *this)
{ }

int TacReader::parse() 
{
    return m_parser.parse();
}

int TacReader::parse(const std::string& filename) 
{
    std::ifstream input;
    input.open(filename);
    switch_input_stream(&input);
    switch_input_stream(nullptr);
    return parse();
}

void TacReader::clear() 
{
    m_instructions.clear();
}

std::string TacReader::str() const {
    std::stringstream s;
    s << "TacReader: " << m_instructions.size() << " commands received from command line." << endl;
    for(uint i = 0; i < m_instructions.size(); i++) {
        s << " * " << m_instructions[i].str() << endl;
    }
    return s.str();
}

void TacReader::switch_input_stream(std::istream *is) {
    m_scanner.switch_streams(is, NULL);
    m_instructions.clear();    
}

void TacReader::add_tac_instruction(const Tac &cmd)
{
    m_instructions.push_back(cmd);
}