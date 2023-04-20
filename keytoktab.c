/**********************************************************************/
/* lab 1 DVG C01 - Driver OBJECT                                      */
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

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
/**********************************************************************/
/* type definitions                                                   */
/**********************************************************************/
typedef struct tab
{
	char *text;
	int token;
} tab;

/**********************************************************************/
/* data objects (tables)                                              */
/**********************************************************************/
static tab tokentab[] = {
	{"id", id},
	{"number", number},
	{":=", assign},
	{"undef", undef},
	{"predef", predef},
	{"tempty", tempty},
	{"error", error},
	{"type", typ},
	{"$", '$'},
	{"(", '('},
	{")", ')'},
	{"*", '*'},
	{"+", '+'},
	{",", ','},
	{"-", '-'},
	{".", '.'},
	{"/", '/'},
	{":", ':'},
	{";", ';'},
	{"=", '='},
	{"TERROR", nfound} // Oh no! Terror
};

static tab keywordtab[] = {
	{"program", program},
	{"input", input},
	{"output", output},
	{"var", var},
	{"begin", begin},
	{"end", end},
	{"boolean", boolean},
	{"integer", integer},
	{"real", real},
	{"KERROR", nfound}};

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Display the tables                                                 */
/**********************************************************************/
void p_toktab()
{
}

/**********************************************************************/
/* lex2tok - convert a lexeme to a token                              */
/**********************************************************************/
toktyp lex2tok(char *fplex)
{
	int tokentab_size = 21;
	for (int i = 0; i < tokentab_size; i++)
	{
		if (!strcmp(fplex, tokentab[i].text))
			return tokentab[i].token;
	}
	return nfound;
}

/**********************************************************************/
/* key2tok - convert a keyword to a token                             */
/**********************************************************************/
toktyp key2tok(char *fplex)
{
	int keywordtab_size = 10;
	for (int i = 0; i < keywordtab_size; i++)
	{
		if (!strcmp(fplex, keywordtab[i].text))
			return keywordtab[i].token;
	}
	return nfound;
}

/**********************************************************************/
/* tok2lex - convert a token to a lexeme                              */
/**********************************************************************/
char *tok2lex(toktyp ftok)
{
	int tokentab_size = 21;
	int keywordtab_size = 10;
	for (int i = 0; i < tokentab_size; i++)
	{
		if (i < tokentab_size && ftok == tokentab[i].token)
			return tokentab[i].text;
		else if (i < keywordtab_size && ftok == keywordtab[i].token)
			return keywordtab[i].text;
	}
	return tokentab[20].text;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
