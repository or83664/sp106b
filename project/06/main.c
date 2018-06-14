#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "code.h"
#include "symbolTable.h"

extern FILE *Instream;
extern int nextAddr;

static char *_toBinaryStr(int addr);

int main(int argc, char **argv) {
	int r;
	unsigned int count = 0;
	
	//for (int i = 0; i < argc; i++)
	//	printf("%d\t%s\n", i, argv[i]);
	if (argc < 1)
		return 1;
	if (r = symbolTableInit())
		return r;
	if (r = Constructor(argv[1]))
		return r;
	
	while(advance() == 0)
	{
		char *s;
		
		switch(commandType())
		{
			case A_COMMAND:
			case C_COMMAND:
				count++;
				break;
			case L_COMMAND:
				s = symbol();
				addEntry(s, count);
				break;
			default:
				break;
		}
	}
	
	ParserRewind();
	
	while(advance() == 0)
	{
		char *s, *bs, *d, *c, *j;
		int a;
		const char *b[3];
		
		switch(commandType())
		{
			case A_COMMAND:
				s = symbol();
				if (sscanf(s, "%d", &a) != 1)
				{
					if (contains(s))
						a = GetAddress(s);
					else if (r = addEntry(s, a = nextAddr++))
					{
						return r;
					}
				}
				bs = _toBinaryStr(a);
				fprintf(stdout, "%s\n", bs);
				break;
			case C_COMMAND:
				d = dest();
				if(d)
					b[0] = Code_dest(d);
				else
					b[0] = "000";
				
				c = comp();
				b[1] = Code_comp(c);
				
				j = jump();
				if (j)
					b[2] = Code_jump(j);
				else
					b[2] = "000";
				
				fprintf(stdout, "111%s%s%s\n", b[1], b[0], b[2]);
				break;
			case L_COMMAND:
				break;
			default:
				break;
		}
	}
	
	return 0;
}

static char *_toBinaryStr(int addr)
{
	static char result[32] = {0};
	
	int i = 0;
	
	while(i < 16)
	{
		result[15 - i] = (addr & 0x01) + '0';
		addr >>= 1;
		i++;
	}
	
	return result;
}
