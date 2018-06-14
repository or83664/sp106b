#ifndef _PARSER_H
#define _PARSER_H

#define A_COMMAND 1
#define C_COMMAND 2
#define L_COMMAND 3

int Constructor(const char *fileName);
int hasMoreCommands(void);
int advance(void);
int commandType(void);
char *symbol(void);
char *dest(void);
char *comp(void);
char *jump(void);

int ParserRewind(void); 

#endif
