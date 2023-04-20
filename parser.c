/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"
#include "lexer.h"          /* when the lexer     is added   */
/* #include "symtab.h"      */ /* when the symtab    is added   */
/* #include "optab.h"       */ /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int lookahead = 0;
static int is_parse_ok = 1;

/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/

/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
static int tokens[] = {program, id, '(', input, ',', output, ')', ';',
                       var, id, ':', integer, ';', begin, id, assign, id, '+', number, '*', number, '*', '(', number, '+', number, ')', ';', end, '$'};

/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
/*static int pget_token()
{
    static int i = 0;
    if (tokens[i] != '$')
        return tokens[i++];
    else
        return '$';
}

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
    
    if (DEBUG)
        printf("\n --------In match expected: %s, found: %s",
               tok2lex(t), tok2lex(lookahead));
    if (lookahead == t)
        lookahead = get_token();
    else
    {
        is_parse_ok = 0;
        printf("\n \e[1;31m*** Unexpected Token: expected: %s found: %s (in match)\e[0m",
               tok2lex(t), tok2lex(lookahead));
        //exit(0);
    }
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/
//___Program___Header___
static void program_header()
{
    if (DEBUG)
        printf("\n *** In  program_header");
    match(program);
    match(id);
    match('(');
    match(input);
    match(',');
    match(output);
    match(')');
    match(';');
}
//______________________

//___var___part_________
void type()
{
    if (lookahead == integer)
        match(integer);
    else if (lookahead == real)
        match(real);
    else if (lookahead == boolean)
        match(boolean);
}
void id_list()
{
    match(id);
    if (lookahead == ',')
    {
        match(',');
        id_list();
    }
}

void var_dec()
{
    id_list();
    match(':');
    type();
    match(';');
}

void var_dec_list()
{
    var_dec();

    if (lookahead == id)
        var_dec_list();
}

void var_part()
{

    match(var);
    var_dec_list();
}
//______________________

//___STAT_PART___

void operand()
{
    if (lookahead == number)
        match(number);
    else
        match(id);
}

void expr(); // Magic :>
void factor()
{
    if (lookahead == '(')
    {
        match('(');
        expr();
        match(')');
    }
    else
        operand();
}

void term()
{
    factor();
    if (lookahead == '*')
    {
        match('*');
        term(); //  -> factor();
    }
}

void expr()
{
    term();
    if (lookahead == '+')
    {
        match('+');
        expr();
    }
}

void assign_stat()
{
    match(id);
    match(assign);
    expr();
}

void stat()
{
    assign_stat();
}

void stat_list()
{
    stat();
    if (lookahead == ';')
    {
        match(';');
        if (lookahead != end)
            stat_list(); // -> another statement.
    }
}

void stat_part()
{
    match(begin);
    stat_list();
    match(end);
    match('.');
}

//______________________

//___PROG___
void prog()
{
    program_header();
    var_part();
    stat_part();
    match('$');
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
    if (DEBUG)
        printf("\n *** In  parser");
    lookahead = get_token(); // get the first token
    prog();                   // call the first grammar rule
    return is_parse_ok;       // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
