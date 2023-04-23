/**********************************************************************/
/* lab 1 DVG C01 - Operator Table OBJECT                              */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1

#define NENTS 4

static int optab[][NENTS] = {
    {'+', integer, integer, integer},
    {'+', real, real, real},
    {'+', integer, real, real},
    {'+', real, integer, real},
    {'*', integer, integer, integer},
    {'*', real, real, real},
    {'*', integer, real, real},
    {'*', real, integer, real},
    {'$', undef, undef, undef}};

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
static int op_tree[256];
static int op_pos = 0;
void op_print_tree()
{
    if (DEBUG)
    {
        printf("\n\e[1;33m");
        for (int i = 0; i < op_pos; i++)
            printf(" %s ", tok2lex(op_tree[i]));
        printf("\e[0m");
    }
}
void init_optree()
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
void add_to_op(toktyp v) { op_tree[op_pos++] = v; }

int get_otype();
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

toktyp digest_expr()
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
    return op_tree[0];
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* display the op tab                                                 */
/**********************************************************************/
void p_optab()
{
    printf("\n________________________________________________________\nTHE OPERATOR TABLE\n________________________________________________________\noperator\targ1\targ2\tresult\n________________________________________________________");
    for (int i = 0; optab[i][0] != '$'; i++)
        printf("\n%8s%12s%10s%10s",
               tok2lex(optab[i][0]),
               tok2lex(optab[i][1]),
               tok2lex(optab[i][2]),
               tok2lex(optab[i][3]));
    printf("\n________________________________________________________");
}

/**********************************************************************/
/* return the type of a binary expression op arg1 arg2                */
/**********************************************************************/
int get_otype(int op, int arg1, int arg2)
{
    for (int i = 0; optab[i][0] != '$'; i++)
        if (op == optab[i][0] && arg1 == optab[i][1] && arg2 == optab[i][2])
            return optab[i][3];
    return undef;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
