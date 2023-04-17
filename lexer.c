/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <ncurses.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define BUFSIZE 1024
#define LEXSIZE 30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int pbuf = 0; /* current index program buffer  */
static int plex = 0; /* current index lexeme  buffer  */

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

static void get_prog()
{
   printf("\n *** TO BE DONE");
}

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/

static void pbuffer()
{
   printf("\n *** TO BE DONE");
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char()
{
   char c = getchar();
   buffer[pbuf++] = c;
}

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/
int is_separator(char c)
{
   if (c == ' ' || c == '\n' || c == '\t')
      return 1;
   else
      return 0;
}

int is_special(char c)
{
   char special[] = {'$','(',')','*','+',',','-','.','/',':',';','='};
   int special_size = 12;
   for (int i = 0; i < special_size; i++)
      if (c == special[i])
         return 1;
   return 0;
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
int get_token()
{
   printf("\n *** TO BE DONE");
   return 0;
}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/


char *get_lexeme()
{
   
   do
   {  // Waits for all separators to be eaten by the buffer. 
      pbuf = 0;
      get_char();
   }
   while (is_separator(buffer[0]));

   // If special, read until not special
   if (is_special(buffer[0]))
   {
      do
      {
         get_char();
      } while (is_special(buffer[pbuf-1]));
      ungetc(buffer[pbuf-1], stdin);   // Back into the input stream
      buffer[pbuf-1] = '\0';
      pbuf = 0;
      memcpy(lexbuf, buffer, strlen(buffer)+1);
      return lexbuf;
   }
   // else if not special, read until special or until separator
   else
   {
      do
      {
         get_char();
      } while (!is_special(buffer[pbuf-1]) && !is_separator(buffer[pbuf-1]));
      ungetc(buffer[pbuf-1], stdin);
      buffer[pbuf-1] = '\0';
      pbuf = 0;      
      memcpy(lexbuf, buffer, strlen(buffer)+1);
      return lexbuf;
   }
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
