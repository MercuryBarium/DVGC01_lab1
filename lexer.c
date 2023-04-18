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
static int end_of_file = 0;

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

   char c;
   if ((c = getchar()) != EOF)
   {
      buffer[pbuf] = c;
      buffer[++pbuf] = '\0';
   }
   else
   {
      end_of_file = 1;
   }
}

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

int is_special(char c)
{
   const static char special[] = {'~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '+', '`', '-', '=', '{', '}',
                                  '[', ']', ':', '"', ';', '\'', '<', '>', '?', ',', '.', '/', '|', '\\', '.'};
   int special_size = 32;
   for (int i = 0; i < special_size; i++)
      if (c == special[i])
         return 1;
   return 0;
}

int identified_indentifier(char *candidate)
{
   if ('a' <= candidate[0] <= 'z' || 'A' <= candidate[0] <= 'Z' || candidate[0] == '_')
   {
   }
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
   {
      pbuf = 0;
      get_char();
   } while (isspace(buffer[0]) && !end_of_file); // Eat the separators :D

   if (is_special(buffer[0]))
   {
      get_char();
      if (!strcmp(buffer, ":="))
      {
         strcpy(lexbuf, buffer);
         return &lexbuf[0];
      }
      else
      {
         ungetc(buffer[pbuf - 1], stdin);
         buffer[pbuf - 1] = '\0';
         strcpy(lexbuf, buffer);
         return &lexbuf[0];
      }
   }
   else if (!is_special(buffer[0]))
   {
      do
      {
         get_char();
      } while (!is_special(buffer[pbuf - 1]) && !isspace(buffer[pbuf - 1]) && !end_of_file);
      ungetc(buffer[pbuf - 1], stdin);
      buffer[pbuf - 1] = '\0';
      strcpy(lexbuf, buffer);
   }
   return &lexbuf[0];
}

int main(void)
{
   while (!end_of_file)
   {
      if (!isspace((get_lexeme())[0]))
         printf("%s\n", lexbuf);
   }
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
