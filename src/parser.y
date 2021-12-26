%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines "_Parser.hpp"
%output "_Parser.cpp"
%define api.parser.class { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { TacRunner }

%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "Tac.hpp"
    using namespace std;

    namespace TacRunner {
        class Lexer;
        class TacReader;
    }
}

// Bison calls yylex() function that must be provided by us to suck tokens
// from the Lexer. This block will be placed at the beginning of IMPLEMENTATION file (cpp).
// We define this function here (function! not method).
// This function is called only inside Bison, so we make it static to limit symbol visibility for the linker
// to avoid potential linking conflicts.
%code top
{
    #include <iostream>
    #include "Lexer.hpp"
    #include "_Parser.hpp"
    #include "TacReader.hpp"
    
    // yylex() arguments are defined in parser.y
    static TacRunner::Parser::symbol_type yylex(TacRunner::Lexer &Lexer, TacRunner::TacReader &driver) {
        return Lexer.get_next_token();
    }
    
    using namespace TacRunner;
}

%lex-param { TacRunner::Lexer &Lexer }
%lex-param { TacRunner::TacReader &driver }
%parse-param { TacRunner::Lexer &Lexer }
%parse-param { TacRunner::TacReader &driver }
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"
%token <std::string> ID  "id";
%token <std::string> STRING  "string";
%token <uint64_t> NUMBER "number";
%token LEFTPAR "leftpar";
%token RIGHTPAR "rightpar";
%token SEMICOLON "semicolon";
%token COMMA "comma";

%type< TacRunner::Tac > tac;
%type< std::vector<uint64_t> > arguments;

%start program

%%

program :   {
                cout << "*** RUN ***" << endl;
                cout << "Type function with list of parmeters. Parameter list can be empty" << endl
                     << "or contain positive integers only. Examples: " << endl
                     << " * function()" << endl
                     << " * function(1,2,3)" << endl
                     << "Terminate listing with ; to see parsed AST" << endl
                     << "Terminate parser with Ctrl-D" << endl;
                
                cout << endl << "prompt> ";
                
                driver.clear();
            }
        | program tac
            {
                const Tac &cmd = $2;
                cout << "tac parsed, updating AST" << endl;
                driver.add_tac_instruction(cmd);
                cout << endl << "prompt> ";
            }
        | program SEMICOLON
            {
                cout << "*** STOP RUN ***" << endl;
                cout << driver.str() << endl;
            }
        ;


tac : ID LEFTPAR RIGHTPAR
        {
            string &id = $1;
            cout << "ID: " << id << endl;
            $$ = Tac(id);
        }
    | ID LEFTPAR arguments RIGHTPAR
        {
            string &id = $1;
            const std::vector<uint64_t> &args = $3;
            cout << "function: " << id << ", " << args.size() << endl;
            $$ = Tac(id, args);
        }
    ;

arguments : NUMBER
        {
            uint64_t number = $1;
            $$ = std::vector<uint64_t>();
            $$.push_back(number);
            cout << "first argument: " << number << endl;
        }
    | STRING
        {
            std::string string = $1;
            $$ = std::vector<std::string>();
            $$.push_back(string);
            cout << "first argument: " << string << endl;
        }
    | arguments COMMA NUMBER
        {
            uint64_t number = $3;
            std::vector<uint64_t> &args = $1;
            args.push_back(number);
            $$ = args;
            cout << "next argument: " << number << ", arg list size = " << args.size() << endl;
        }
    ;
    
%%

// Bison expects us to provide implementation - otherwise linker complains
void TacRunner::Parser::error(const std::string &message) {
        
        // Location should be initialized inside Lexer action, but is not in this example.
        // Let's grab location directly from driver class.
	    // cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl;
}