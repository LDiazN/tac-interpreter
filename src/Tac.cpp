
#include "Tac.hpp"

#include <iostream>
#include <sstream>

using namespace TacRunner;
using std::cout;
using std::endl;

Tac::Tac(const std::string &name, const std::vector<uint64_t> arguments) :
    m_name(name),
    m_args(arguments)
{
}

Tac::Tac(const std::string &name) :
    m_name(name),
    m_args()
{
}

Tac::Tac() :
    m_name(),
    m_args()
{
}

Tac::~Tac()
{
}
    
std::string Tac::str() const {
    std::stringstream ts;
    ts << "name = [" << m_name << "], ";
    ts << "arguments = [";
    
    for(int i = 0; i < m_args.size(); i++) {
        ts << m_args[i];
        if(i < m_args.size() - 1) {
            ts << ", ";
        }
    }
    
    ts << "]";
    return ts.str();
}

std::string Tac::name() const {
    return m_name;
}