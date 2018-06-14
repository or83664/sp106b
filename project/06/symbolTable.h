#ifndef _SYMBOLTABLE_H 
#define _SYMBOLTABLE_H

int symbolTableInit(void);
int addEntry(const char *symbol,int address);
int contains(const char *symbol);
int GetAddress(const char *symbol);

#endif
