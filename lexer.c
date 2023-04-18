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
#include "keytoktab.c"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define BUFSIZE 1024
#define LEXSIZE 30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE] = "TERROR";
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

int is_number(char *cand)
{
   
}

int identified_indentifier(char *cand)
{
   if (strlen(cand) && !is_special(cand[0]))
      return 1;
   return 0;
}
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
char * get_lexeme();
int get_token()
{
   get_lexeme();
   if (!end_of_file && strlen(lexbuf))
   {
      int ret;
      if ((ret=lex2tok(lexbuf))!=nfound)
         return ret;
      else if ((ret=key2tok(lexbuf))!=nfound)
         return ret;
      else if (identified_indentifier(lexbuf))
         return id;
      else
         return nfound;
   } else
      return '$';
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
         return lexbuf;
      }
      else
      {
         ungetc(buffer[pbuf - 1], stdin);
         buffer[pbuf - 1] = '\0';
         strcpy(lexbuf, buffer);
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
   if (isspace(lexbuf[0])) lexbuf[0] = '\0';
   return lexbuf;
}

int main() 
{
   while (!end_of_file)
   {
      int t = get_token();
      printf("%s\t|\t%s\n", lexbuf, tok2lex(t));
   }
   
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
