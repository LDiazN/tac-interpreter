// Local Includes
#include "Tac.hpp"

// C++ Includes
#include <iostream>
#include <sstream>
#include <assert.h>

using namespace TacRunner;
using std::cout;
using std::endl;

std::string TacRunner::instr_to_str(Instr instr)
{
    switch (instr)
    {
    case Instr::METASTATICV:
        return "@staticv";
        break;
    case Instr::METALABEL:
        return "@label";
        break;
    case Instr::METASTRING:
        return "@string";
        break;
    case Instr::ASSIGNW:
        return "assignw";
        break;
    case Instr::ASSIGNB:
        return "assignb";
        break;
    case Instr::ADD:
        return "add";
        break;
    case Instr::SUB:
        return "sub";
        break;
    case Instr::MULT:
        return "mult";
        break;
    case Instr::DIV:
        return "div";
        break;
    case Instr::MOD:
        return "mod";
        break;
    case Instr::MINUS:
        return "minus";
        break;
    case Instr::NEG:
        return "neg";
        break;
    case Instr::EQ:
        return "eq";
        break;
    case Instr::NEQ:
        return "neq";
        break;
    case Instr::LT:
        return "lt";
        break;
    case Instr::LEQ:
        return "leq";
        break;
    case Instr::GT:
        return "gt";
        break;
    case Instr::GEQ:
        return "geq";
        break;
    case Instr::GOTO:
        return "goto";
        break;
    case Instr::GOIF:
        return "goif";
        break;
    case Instr::GOIFNOT:
        return "goifnot";
        break;
    case Instr::MALLOC:
        return "malloc";
        break;
    case Instr::MEMCPY:
        return "memcpy";
        break;
    case Instr::FREE:
        return "free";
        break;
    case Instr::EXIT:
        return "exit";
        break;
    case Instr::RETURN:
        return "return";
        break;
    case Instr::PARAM:
        return "param";
        break;
    case Instr::CALL:
        return "call";
        break;
    case Instr::PRINTI:
        return "printi";
        break;
    case Instr::PRINTF:
        return "printf";
        break;
    case Instr::PRINT:
        return "print";
        break;
    case Instr::PRINTC:
        return "printc";
        break;
    case Instr::READI:
        return "readi";
        break;
    case Instr::READF:
        return "readf";
        break;
    case Instr::READ:
        return "read";
        break;
    case Instr::READC:
        return "readc";
        break;
    case Instr::METAFUNBEGIN:
        return "@fun_begin";
        break;
    case Instr::METAFUNEND:
        return "@fun_end";
        break;
    default:
        assert(false && "Invalid variand for Instr enum");
        break;
    }

    return "";
}

std::string Variable::str() const
{
    std::stringstream ss;
    ss << name;
    if (is_access)
        ss << "[" << index << "]";
    
    return ss.str();
}

std::string Value::str() const
{
    // String where to store result
    std::stringstream ss;

    if (is<Variable>())
    {
        auto v = get<Variable>();
        if (v.is_access) // Format as name[index]
            ss << v.name << "[" << v.index << "]";
        else             // Format as name
            ss << v.name;
    }
    else if (is<char>())
    {
        auto c = get<char>();
        ss << c;
    }
    else if(is<bool>())
    {
        auto b = get<bool>();
        ss << b;
    }
    else if (is<int>())
    {
        auto i = get<int>();
        ss << i;
    }
    else if (is<float>())
    {
        auto f = get<float>();
        ss << f;
    }
    else if (is<std::string>())
    {
        auto s = get<std::string>();
        ss << '"' << s << '"';
    }
    else 
    {
        assert(false && "Unexpected type for value");
    }

    return ss.str();
}

Tac::Tac(Instr &inst) 
    : m_instr(inst)
    , m_args({})
{ }

Tac::Tac(Instr &inst, const Value argument)
    : m_instr(inst)
    , m_args({argument})
{ }

Tac::Tac(Instr &inst, const Value argument1, const Value argument2)
    : m_instr(inst)
    , m_args({argument1, argument2})
{ }
Tac::Tac(Instr &inst, const Value argument1, const Value argument2, const Value argument3)
    : m_instr(inst)
    , m_args({argument1, argument2, argument3})
{ }

Tac::~Tac()
{ }
    
std::string Tac::str() const {
    std::stringstream ts;
    ts << "name = [" << instr_to_str(m_instr) << "], ";
    ts << "arguments = [";
    
    for(uint i = 0; i < m_args.size(); i++) {
        ts << m_args[i].str();
        if(i < m_args.size() - 1) {
            ts << ", ";
        }
    }
    
    ts << "]";
    return ts.str();
}