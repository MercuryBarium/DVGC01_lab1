//  Marcus Brülls

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
#include "lexer.h"  /* when the lexer     is added   */
#include "symtab.h" /* when the symtab    is added   */
#include "optab.h"  /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int lookahead = 0;
static int is_parse_ok = 1;
char lexeme[50] = "\0";

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
static toktyp id_type = undef;
static int op_tree[256];
static int op_pos = 0;
static void op_print_tree()
{
    if (DEBUG)
    {
        printf("\n\e[1;33m");
        for (int i = 0; i < op_pos; i++)
            printf(" %s ", tok2lex(op_tree[i]));
        printf("\e[0m");
    }
}
static void init_optree()
{
    op_pos = 0;
    for (int i = 0; i < 256; i++)
        op_tree[i] = nfound;
}

static void op_remove(int x)
{
    for (int i = x; i < op_pos; i++)
    {
        if (i == x)
            op_tree[i] = nfound;
        else
            op_tree[i - 1] = op_tree[i];
    }
    op_pos--;
}
static void add_to_op(toktyp v) { op_tree[op_pos++] = v; }


static void relax(int i, toktyp o, int op_end)
{
    for (int j = i; j + 2 < op_end; j++)
    {
        if ((op_tree[j] == integer || op_tree[j] == real) && op_tree[j + 1] == o && (op_tree[j + 2] == integer || op_tree[j + 2] == real))
        {
            op_tree[j] = get_otype(op_tree[j + 1], op_tree[j], op_tree[j + 2]);
            op_remove(j + 2);
            op_remove(j + 1);
            j--;
        }
    }
}

static void relax_parentheses()
{
    for (int i = op_pos - 1; i >= 0; i--)
    {
        if (op_tree[i] == '(')
        {
            int x = i + 1;
            while (x < op_pos)
            {
                if (op_tree[x] == ')')
                {
                    op_remove(x);
                    relax(i, '+', x);
                    op_remove(i);
                    break;
                }
                else
                    x++;
            }
            op_print_tree();
        }
    }
}

static toktyp digest_expr()
{
    for (int i = 0; i < op_pos; i++)
        if (op_tree[i] == boolean)
            return undef;
    relax(0, '*', op_pos);
    op_print_tree();

    relax_parentheses();

    relax(0, '*', op_pos);
    op_print_tree();

    relax(0, '+', op_pos);
    op_print_tree();
    if (op_pos == 1)
        return op_tree[0];
    else
        return undef;
}   

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{

    if (DEBUG)
        printf("\n --------In match expected: %s, found: %s",
               tok2lex(t), tok2lex(lookahead));
    if (lookahead == t)
    {
        strcpy(lexeme, get_lexeme());
        lookahead = get_token();
    }
    else
    {
        is_parse_ok = 0;
        printf("\n \e[1;31m*** Unexpected Token: expected: %s found: %s (in match)\e[0m",
               tok2lex(t), tok2lex(lookahead));
        // exit(0);
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
    addp_name(lexeme);
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
    {
        setv_type(integer);
        match(integer);
    }
    else if (lookahead == real)
    {
        setv_type(real);
        match(real);
    }
    else if (lookahead == boolean)
    {
        setv_type(boolean);
        match(boolean);
    }
}
void id_list()
{
    if (lookahead == id)
    {
        if (!find_name(lexeme))
            addv_name(lexeme);
        else
        {    
            printf("\n\e[1;31mSEMANTICS: ID already declared. %s \e[0m", lexeme);
            is_parse_ok = 0;
        }
    }
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
    {
        add_to_op(integer);
        match(number);
    }
    else
    {
        if (!find_name(lexeme))
        {
            printf("\n\e[1;31mSEMANTICS: Undeclared variable name referenced: %s\e[0m", lexeme);
            is_parse_ok = 0;
        }
        add_to_op(get_ntype(lexeme));
        match(id);
    }
}

void expr(); // Magic :>
void factor()
{
    if (lookahead == '(')
    {
        add_to_op(lookahead);
        match('(');
        expr();
        add_to_op(lookahead);
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
        add_to_op('*');
        match('*');
        term(); //  -> factor();
    }
}

void expr()
{
    term();
    if (lookahead == '+')
    {
        add_to_op('+');
        match('+');
        expr();
    }
}

void assign_stat()
{
    if (!find_name(lexeme))
    {
        printf("\n\e[1;31mSEMANTICS: Undeclared variable name referenced: %s\e[0m", lexeme);
        is_parse_ok = 0;
    }
    id_type = get_ntype(lexeme);
    match(id);
    match(assign);
    expr();
}

void stat()
{
    init_optree(); // operation_buffer
    assign_stat();
    op_print_tree();
    toktyp t;
    if ((t=digest_expr()) != id_type)
    {
        is_parse_ok = 0;
        printf("\n\e[1;31mSEMANTICS: Expression invalidated: %s != %s\e[0m", tok2lex(id_type), tok2lex(t));
    } else {
        printf("\n\e[1;32mSEMANTICS: Expression validated\e[0m");
    }
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
    while (lookahead == var)
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
    if (!strlen(lexeme))
        strcpy(lexeme, get_lexeme());
    lookahead = get_token(); // get the first token
    prog();                  // call the first grammar rule
    p_symtab();
    return is_parse_ok; // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
