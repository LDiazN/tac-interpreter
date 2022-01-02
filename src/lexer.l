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

integer         (([1-9][0-9]*)|0)
float           (({frac}{exp_opt})|({dseq}{exp}))

id              ([a-zA-Z_@]+[a-zA-Z_@0-9]*) 
ascii_char      ([\x00-\x7F])
string          ((\"{ascii_char}*\"))

single_line_comment #[^\n\r]+?(?:\*\)|[\n\r])

%%

{single_line_comment}         { ; }
"@staticv"  {
                return TacRunner::Parser::make_METASTATICV(TacRunner::Instr::METASTATICV);
            }

"@string"   {
                return TacRunner::Parser::make_METASTRING(TacRunner::Instr::METASTRING);
            }

"@label"    {
                return TacRunner::Parser::make_METALABEL(TacRunner::Instr::METALABEL);
            }

"assignw"   {
                return TacRunner::Parser::make_ASSIGNW(TacRunner::Instr::ASSIGNW);
            }

"assignb"   {
                return TacRunner::Parser::make_ASSIGNB(TacRunner::Instr::ASSIGNB);
            }

"add"       {
                return TacRunner::Parser::make_ADD(TacRunner::Instr::ADD);
            }
"sub"       {
                return TacRunner::Parser::make_SUB(TacRunner::Instr::SUB);
            }
"mult"      {
                return TacRunner::Parser::make_MULT(TacRunner::Instr::MULT);
            }
"div"       {
                return TacRunner::Parser::make_DIV(TacRunner::Instr::DIV);
            }
"mod"       {
                return TacRunner::Parser::make_MOD(TacRunner::Instr::MOD);
            }
"minus"     {
                return TacRunner::Parser::make_MINUS(TacRunner::Instr::MINUS);
            }
"neg"       {
                return TacRunner::Parser::make_NEG(TacRunner::Instr::NEG);
            }
"eq"        {
                return TacRunner::Parser::make_EQ(TacRunner::Instr::EQ);
            }
"neq"       {
                return TacRunner::Parser::make_NEQ(TacRunner::Instr::NEQ);
            }
"lt"        {
                return TacRunner::Parser::make_LT(TacRunner::Instr::LT);
            }
"leq"       {
                return TacRunner::Parser::make_LEQ(TacRunner::Instr::LEQ);
            }
"gt"        {
                return TacRunner::Parser::make_GT(TacRunner::Instr::GT);
            }

"geq"       {
                return TacRunner::Parser::make_GEQ(TacRunner::Instr::GEQ);
            }

"goto"      {
                return TacRunner::Parser::make_GOTO(TacRunner::Instr::GOTO);
            }
            
"goif"      {
                return TacRunner::Parser::make_GOIF(TacRunner::Instr::GOIF);
            }
            
"goifnot"   {
                return TacRunner::Parser::make_GOIFNOT(TacRunner::Instr::GOIFNOT);
            }    
            
"malloc"    {
                return TacRunner::Parser::make_MALLOC(TacRunner::Instr::MALLOC);
            }    
            
"memcpy"    {
                return TacRunner::Parser::make_MEMCPY(TacRunner::Instr::MEMCPY);
            }    
            
"free"      {
                return TacRunner::Parser::make_FREE(TacRunner::Instr::FREE);
            }
            
"exit"      {
                return TacRunner::Parser::make_EXIT(TacRunner::Instr::EXIT);
            }
            
"return"    {
                return TacRunner::Parser::make_RETURN(TacRunner::Instr::RETURN);
            }    
            
"param"     {
                return TacRunner::Parser::make_PARAM(TacRunner::Instr::PARAM);
            }
            
"call"      {
                return TacRunner::Parser::make_CALL(TacRunner::Instr::CALL);
            }
            
"printi"    {
                return TacRunner::Parser::make_PRINTI(TacRunner::Instr::PRINTI);
            }    
            
"printf"    {
                return TacRunner::Parser::make_PRINTF(TacRunner::Instr::PRINTF);
            }    
            
"print"     {
                return TacRunner::Parser::make_PRINT(TacRunner::Instr::PRINT);
            }
            
"printc"    {
                return TacRunner::Parser::make_PRINTC(TacRunner::Instr::PRINTC);
            }    
            
"readi"     {
                return TacRunner::Parser::make_READI(TacRunner::Instr::READI);
            }
            
"readf"     {
                return TacRunner::Parser::make_READF(TacRunner::Instr::READF);
            }
            
"read"      {
                return TacRunner::Parser::make_READ(TacRunner::Instr::READ);
            }
            
"readc"     {
                return TacRunner::Parser::make_READC(TacRunner::Instr::READC);
            }
            

"@fun_begin" {
                return TacRunner::Parser::make_METAFUNBEGIN(TacRunner::Instr::METAFUNBEGIN);
             }

"@fun_end"   {
                return TacRunner::Parser::make_METAFUNEND(TacRunner::Instr::METAFUNEND);
             }

"["         {
                return TacRunner::Parser::make_LBRACKET();
            }

"]"         {
                return TacRunner::Parser::make_RBRACKET();
            }

{string}    {
                return TacRunner::Parser::make_STRING(yytext); 
            }

"False"     {
                return TacRunner::Parser::make_BOOL(false);
            }

"True"      {
                return TacRunner::Parser::make_BOOL(true);
            }

{integer}   {
                int number = stoi(yytext);
                return TacRunner::Parser::make_INTEGER(number);
            }

{float}     {
                float number = stof(yytext);
                return TacRunner::Parser::make_FLOAT(number);
            }

\'{ascii_char}\' { return TacRunner::Parser::make_CHAR(yytext[1]); }

\(          {
                return TacRunner::Parser::make_LEFTPAR();
            }
            
\)          { 
                return TacRunner::Parser::make_RIGHTPAR();
            }
            
,           {
                return TacRunner::Parser::make_COMMA();
            }
            
[\r\t ]     {
                //cout << "Scanner: whitechar (ignored)" << endl;
            }

[\n]        {
                return TacRunner::Parser::make_NEWLINE();
            }

{id}        {
                return TacRunner::Parser::make_ID(yytext); 
            }

.           { 
                cout << "Scanner: unknown character [" << yytext << "]" << endl; 
            }
            
<<EOF>>     { return yyterminate(); }


%%