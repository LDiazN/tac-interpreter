#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>

#include "Lexer.hpp"

// autogenerated by Bison, don't panic
// if your IDE can't resolve it - call make first
#include "_Parser.hpp"

namespace TacRunner {

// forward declare our simplistic AST node class so we
// can declare container for it without the header
class Tac;

/**
 * This class is the interface for our scanner/lexer. The end user
 * is expected to use this. It drives scanner/lexer, keeps
 * parsed AST and generally is a good place to store additional
 * context data. Both parser and lexer have access to it via internal 
 * references.
 * 
 * I know that the AST is a bit too strong word for a simple
 * vector with nodes, but this is only an example. Get off me.
 */
class TacReader
{
public:
    TacReader();
    
    /**
     * Run parser. Results are stored inside.
     * @return 0 on success, 1 on failure
     */
    int parse();
    
    /**
     * @brief Run parser over a file given by name
     * 
     * @param filename file where to read tokens from
     * @return Success status, 0 on success, 1 on failure
     */
    int parse(const std::string& filename);

    /**
     * Clear AST
     */
    void clear();
    
    /**
     * Print AST
     */
    std::string str() const;
    
    /**
     * Switch scanner input stream. Default is standard input (std::cin).
     * It will also reset AST.
     */
    void switch_input_stream(std::istream *is);
    
    /**
     * This is needed so that Scanner and Parser can call some
     * methods that we want to keep hidden from the end user.
     */
    friend class Parser;
    friend class Scanner;
    
private:
    // Used internally by Parser to insert AST nodes.
    void add_tac_instruction(const Tac &cmd);
    
    // Used to get last Scanner location. Used in error messages.
    unsigned int location() const;
    
private:
    std::vector<Tac> m_instructions; // Tac Program
    Lexer m_scanner;                 // Scanner object
    Parser m_parser;                 // Parser object
};

}

#endif // INTERPRETER_H