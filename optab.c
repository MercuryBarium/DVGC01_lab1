//  Marcus Brülls

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
    {'/', integer, integer, integer},
    {'/', integer, real, real},
    {'/', real, integer, real},
    {'/', real, real, real},
    {'-', integer, integer, integer},
    {'-', integer, real, real},
    {'-', real, integer, real},
    {'-', real, real, real},
    {'$', undef, undef, undef},
};

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

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
