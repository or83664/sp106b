#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

FILE *Instream = NULL; 
static char currentCommand[256];
static int lastType = 0;

int Constructor(const char *fileName){
	Instream = fopen(fileName,"r");
	if (NULL == Instream){
		fprintf(stderr, "Input an error file\n");//stderr-->¼Ð·Ç¿é¥X 
		return 1;
	}
	else{
		memset(currentCommand, 0, sizeof(currentCommand));
		return 0;
	}
}

//if true return 0,else return 1
int hasMoreCommands(void){
	if (Instream){
		return (feof(Instream)?0:1);
	}
	else{
		return 0;
	}
}

int advance(void){
	char *comment;
	char *chLine;
	char *space = currentCommand, *end;
	if (Instream){
		if(fgets(currentCommand, sizeof(currentCommand), Instream)){
			comment = strstr(currentCommand,"//");
			if (comment)
				*comment = '\0';
			chLine = strstr(currentCommand,"\n");
			if (chLine)
				*chLine = '\0';

			while (*space == ' ' || *space == '\t'){
				space++;
			}
			if (strlen(currentCommand) > 0)
			{
				end = currentCommand + strlen(currentCommand) - 1;
				while (*end == ' ' || *end == '\t'){
					end--;
				}
				*(++end) = '\0';
			}
			
			memmove(currentCommand, space, strlen(space) + 1);
			return 0;
		}
	}
	return 1;
}

int commandType(void){
	if (strlen(currentCommand)==0){
		return lastType = 0;//this is a empty string
	}
	if(currentCommand[0]=='@'){
		return lastType = A_COMMAND;
	}
	if (strlen(currentCommand)<2){
		return lastType = 0;//this is a empty string
	}
	if(currentCommand[0]=='('&&currentCommand[strlen(currentCommand)-1]==')'){
		return lastType = L_COMMAND;
	} 
	
	return lastType = C_COMMAND;
}

char repeator[256] ; 
char *symbol(void){
	if (lastType == A_COMMAND){	
		memcpy(repeator,currentCommand+1, strlen(currentCommand));
		return repeator;
	}
	
	if (lastType == L_COMMAND){
		memcpy(repeator,currentCommand+1, strlen(currentCommand)-2);
		repeator[strlen(currentCommand)-2] = '\0';
		return repeator;
	}
	
	return NULL;
}

char *dest(void){
	char *equal;
	if (equal =strstr(currentCommand,"=")){
		size_t len = ((size_t)equal-(size_t)currentCommand) / sizeof(currentCommand[0]);
		memcpy(repeator,currentCommand, len);
		repeator[len] = '\0';
		return repeator;
	}
	return NULL;
}

char *comp(void){
	char *start;
	char *end;
	size_t len;
	
	start =strstr(currentCommand,"=");
	end = strstr(currentCommand,";");
	if(start == NULL)
		start = currentCommand;
	else
		start = start + 1;
	if(end == NULL)
		end = currentCommand + strlen(currentCommand);
	len = (size_t)end-(size_t)start;
	memcpy(repeator,start, len);
	repeator[len] = '\0';
	return repeator;
}

char *jump(void){
	char *start;
	start =strstr(currentCommand,";");
	if (start == NULL)
		return NULL;
	else 
        memcpy(repeator,start+1, strlen(start+1)+1);
    return repeator;
}

int ParserRewind(void)
{
	if (Instream)
		rewind(Instream);
	else
		return 1;
	return 0;
}
