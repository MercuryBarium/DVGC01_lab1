/**********************************************************************/
/* constants & public functions                                       */
/**********************************************************************/

#ifndef OPTAB_H
#define OPTAB_H

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
#include "keytoktab.h"

void   p_optab();                            /* display the optab     */


void op_print_tree();
void init_optree();
void add_to_op(toktyp v);
toktyp digest_expr();

toktyp get_otype( toktyp op, toktyp arg1, toktyp arg2);

#endif

/**********************************************************************/
/* end of definitions                                                 */
/**********************************************************************/
