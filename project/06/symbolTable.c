#include <stdlib.h>
#include <string.h>

int nextAddr = 16;

typedef struct {
	const char *symbol;
    int address;
} entry_t;

entry_t *pairTable;
unsigned int count;
unsigned int capacity;

int addEntry(const char *symbol,int address);
int symbolTableInit(void)
{
	count = 0;
	capacity = 128;
	pairTable = (entry_t *)malloc(sizeof(*pairTable) * capacity);
	if (pairTable == NULL)
		return 1;
	else
	{
		addEntry("SRCEEN",16384);
		addEntry("KBD",24576);
		addEntry("SP",0);
		addEntry("LCL",1);
		addEntry("ARG",2);
		addEntry("THIS",3);
		addEntry("THAT",4);
		addEntry("R0",0);
		addEntry("R1",1);
		addEntry("R2",2);
		addEntry("R3",3);
		addEntry("R4",4);
		addEntry("R5",5);
		addEntry("R6",6);
		addEntry("R7",7);
		addEntry("R8",8);
		addEntry("R9",9);
		addEntry("R10",10);
		addEntry("R11",11);
		addEntry("R12",12);
		addEntry("R13",13);
		addEntry("R14",14);
		addEntry("R15",15);
		return 0;
	}
		
}

int addEntry(const char *symbol,int address){
	entry_t obj = {symbol, address};
	if(count == capacity)
	{
		capacity <<= 1; // faster than *2
		pairTable = (entry_t *)realloc(pairTable, sizeof(*pairTable) * capacity);
		if (pairTable == NULL)
			return 1;
	}
	pairTable[count] = obj; //²L¼h½Æ»s 
	count++;
	return 0;
}

int contains(const char *symbol){
	for (unsigned int i=0;i<count;i++){
		if (strcmp(pairTable[i].symbol,symbol)==0)
		{
			return -1;//boolean true
		}
	}
	return 0;
}

int GetAddress(const char *symbol){
	for (unsigned int i=0;i<count;i++){
		if (strcmp(pairTable[i].symbol,symbol)==0)
		{
			return pairTable[i].address;//boolean true
		}
	}
	return -100;//while not found
}
