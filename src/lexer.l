%{
	#include <iostream>
	#include <cstdlib>
	#include "Lexer.hpp"
	#include "TacReader.hpp"
	#include "_Parser.hpp"

	using namespace std;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() TacRunner::Parser::make_END();
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Lexer"
%option prefix="TacRunner_"
%option outfile="_Lexer.cpp"
%option header-file="_Lexer.hpp"

dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)

integer         ({dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))

id              ([a-zA-Z_@]+[a-zA-Z_@0-9]*) 
ascii_char      ([\x00-\x7F])
string          ((\"{ascii_char}*\"))

%%

{id}        {
                cout << "Scanner: identifier [" << yytext << "]" << endl;
                return TacRunner::Parser::make_ID(yytext); 
            }

{string}    {
                cout << "Scanner: string [" << yytext << "]" << endl;
                return TacRunner::Parser::make_STRING(yytext); 
            }
            
\(          {
                cout << "Scanner: '('" << endl;
                return TacRunner::Parser::make_LEFTPAR();
            }
            
\)          { 
                cout << "Scanner: ')'" << endl;
                return TacRunner::Parser::make_RIGHTPAR();
            }
            
;           {
                cout << "Scanner: ';'" << endl;
                return TacRunner::Parser::make_SEMICOLON();
            }
            
,           {
                cout << "Scanner: ','" << endl;
                return TacRunner::Parser::make_COMMA();
            }
            
[\n\t ]     {
                //cout << "Scanner: whitechar (ignored)" << endl;
            }

[1-9][0-9]* {
                cout << "Scanner: decimal number: " << yytext << endl;
                uint64_t number = strtoull(yytext, 0, 10);
                return TacRunner::Parser::make_NUMBER(number);
            }

.           { 
                cout << "Scanner: unknown character [" << yytext << "]" << endl; 
            }
            
<<EOF>>     { return yyterminate(); }


%%