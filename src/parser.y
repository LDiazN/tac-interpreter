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
%token <int> INTEGER "integer";
%token <float> FLOAT "float";
%token <bool> BOOL "bool";
%token <char> CHAR "char";

%token RBRACKET "rbracket";
%token LBRACKET "lbracket";
%token LEFTPAR "leftpar";
%token RIGHTPAR "rightpar";
%token COMMA "comma";

%token <TacRunner::Instr> METASTATICV    "@staticv";
%token <TacRunner::Instr> METALABEL  "@label";
%token <TacRunner::Instr> METASTRING     "@string";
%token <TacRunner::Instr> ASSIGNW    "assignw";
%token <TacRunner::Instr> ASSIGNB    "assignb";
%token <TacRunner::Instr> ADD    "add";
%token <TacRunner::Instr> SUB    "sub";
%token <TacRunner::Instr> MULT   "mult";
%token <TacRunner::Instr> DIV    "div";
%token <TacRunner::Instr> MOD    "mod";
%token <TacRunner::Instr> MINUS  "minus";
%token <TacRunner::Instr> NEG    "neg";
%token <TacRunner::Instr> EQ     "eq";
%token <TacRunner::Instr> NEQ    "neq";
%token <TacRunner::Instr> LT     "lt";
%token <TacRunner::Instr> LEQ    "leq";
%token <TacRunner::Instr> GT     "gt";
%token <TacRunner::Instr> GEQ    "geq";
%token <TacRunner::Instr> GOTO   "goto";
%token <TacRunner::Instr> GOIF   "goif";
%token <TacRunner::Instr> GOIFNOT    "goifnot";
%token <TacRunner::Instr> MALLOC     "malloc";
%token <TacRunner::Instr> MEMCPY     "memcpy";
%token <TacRunner::Instr> FREE   "free";
%token <TacRunner::Instr> EXIT   "exit";
%token <TacRunner::Instr> RETURN     "return";
%token <TacRunner::Instr> PARAM  "param";
%token <TacRunner::Instr> CALL   "call";
%token <TacRunner::Instr> PRINTI     "printi";
%token <TacRunner::Instr> PRINTF     "printf";
%token <TacRunner::Instr> PRINT  "print";
%token <TacRunner::Instr> PRINTC     "printc";
%token <TacRunner::Instr> READI  "readi";
%token <TacRunner::Instr> READF  "readf";
%token <TacRunner::Instr> READ   "read";
%token <TacRunner::Instr> READC  "readc";
%token <TacRunner::Instr> METAFUNBEGIN   "@fun_begin";
%token <TacRunner::Instr> METAFUNEND     "@fun_end";

%token NEWLINE "newline";

%type < TacRunner::Value > Constant;
%type < std::vector<TacRunner::Tac> > Data;
%type < TacRunner::Tac > D;
%type < std::vector<TacRunner::Tac> > Text;
%type < TacRunner::Tac > T;
%type < std::vector<TacRunner::Tac> > F;
%type < TacRunner::Value > LValue;
%type < TacRunner::Value > RValue;
%type < TacRunner::Value > Value;
%type < TacRunner::Variable > Access;
%type < TacRunner::Variable > Variable;


%start Program

%%

Program : Data Text 
                { 
                    auto &ds = $1;
                    for (int i = ds.size() - 1; i >= 0; i--)
                    {
                        auto &d = ds[i];
                        driver.add_tac_instruction(d);
                    }

                    auto &ts = $2;
                    for (int i = ts.size() - 1; i >= 0; i--)
                    {
                        auto &d = ts[i];
                        driver.add_tac_instruction(d);
                    }
                }

Data    : %empty {  
                    std::vector<Tac> tac_instrs;
                    $$ = tac_instrs;
                 }

        | D Data {
                    std::vector<Tac> &instrs = $2; // get instruction vector in Data
                    instrs.push_back($1);          // Add instructions to instruction list
                    $$ = instrs;
                 }

D       : METASTATICV ID INTEGER NEWLINE   
            {
                TacRunner::Tac t($1, TacRunner::Value($2), TacRunner::Value($3));
                $$ = t;
            }
        | METASTRING ID STRING NEWLINE
            {
                TacRunner::Tac t($1, TacRunner::Value($2), TacRunner::Value($3));
                $$ = t;
            }

Text    : %empty 
                {  
                    std::vector<Tac> tac_instrs;
                    $$ = tac_instrs;
                }
        | T NEWLINE Text 
                {
                    std::vector<Tac> &instrs = $3; // get instruction vector in Text
                    instrs.push_back($1);          // Add instructions to instruction list
                    $$ = instrs;
                }

        | F NEWLINE Text 
                {
                    std::vector<Tac> &instrs = $3;      // get instruction vector in Text
                    auto &new_instrs = $1;              // get function instructions
                    instrs.reserve(instrs.size() + new_instrs.size());   // Add instructions to instruction list
                    // copy new instructions to vector with instructions
                    for(auto& inst : new_instrs)
                        instrs.push_back(inst);

                    $$ = instrs;
                }

T       : METALABEL ID
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }

        | ASSIGNW LValue RValue
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3);
                }
        | ASSIGNB LValue RValue
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3);
                }
        | ADD     Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | SUB     Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | MULT    Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | DIV     Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | MOD     Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | MINUS   Variable Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3);
                }
        | NEG Variable Value
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3);
                }
        | EQ      Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | NEQ     Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | LT      Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | LEQ     Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | GT      Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | GEQ     Variable Value Value 
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3, $4);
                }
        | GOTO  ID
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }
        | GOIF  ID Value
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3);
                }
        | GOIFNOT ID Value
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3);
                }
        | MALLOC  Variable Value
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), $3);
                }
        | MEMCPY Variable Variable INTEGER
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), TacRunner::Value($3), TacRunner::Value($4));
                }

        | FREE  LValue
                {
                    $$ = TacRunner::Tac($1, $2);
                }
        | EXIT    Value
                {
                    $$ = TacRunner::Tac($1, $2);
                }
        | RETURN  Value
                {
                    $$ = TacRunner::Tac($1, $2);
                }
        | PARAM LValue RValue 
                {
                    $$ = TacRunner::Tac($1, $2, $3);
                }
        | CALL Variable ID
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2), TacRunner::Value($3));
                }
        | PRINTI Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }
        | PRINTF Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }
        | PRINT  Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }
        | PRINTC  Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }
        | READI Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }
        | READF Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }
        | READ  Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }

        | READC  Variable
                {
                    $$ = TacRunner::Tac($1, TacRunner::Value($2));
                }

F       :   METAFUNBEGIN ID INTEGER NEWLINE 
            Text NEWLINE 
            METAFUNEND INTEGER NEWLINE 
                {
                    TacRunner::Tac t1($1, TacRunner::Value($2), TacRunner::Value($3));
                    TacRunner::Tac t2($7, TacRunner::Value($8));
                    auto instrs = $5;
                    std::vector<TacRunner::Tac> new_instrs;
                    // Create a new vector and reserve enough space 
                    // as pushing from the start has to reallocate the
                    // entire vector anyways
                    new_instrs.reserve(instrs.size() + 2);

                    // Copy footer (this will be reversed in another rule)
                    new_instrs.push_back(t2);

                    // Copy intermediate instructions
                    for(auto &i : instrs)
                        new_instrs.push_back(i);
                    
                    $$ = new_instrs;
                }

Constant : BOOL    {
                       TacRunner::Value b($1);
                       $$ = b;
                    }
         | INTEGER  {
                        TacRunner::Value b($1);
                        $$ = b;
                    }
         | FLOAT    {
                        TacRunner::Value b($1);
                        $$ = b;
                    }
         | CHAR     {
                        TacRunner::Value b($1);
                        $$ = b;
                    }

Access : ID LBRACKET INTEGER RBRACKET 
            {
                $$ = TacRunner::Variable{$1, $3, true};
            }
Variable : ID { $$ = TacRunner::Variable{$1, 0, false}; } 

LValue  : Variable { $$ = TacRunner::Value($1); }
        | Access   { $$ = TacRunner::Value($1); }

Value   : Constant { $$ = $1; }
        | Variable { $$ = TacRunner::Value($1); }

RValue  : Value     { $$ = $1; }
        | Access    { $$ = TacRunner::Value($1); }

%%

// Bison expects us to provide implementation - otherwise linker complains
void TacRunner::Parser::error(const std::string &message) {
        
        // Location should be initialized inside Lexer action, but is not in this example.
        // Let's grab location directly from driver class.
	    // cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl;
}