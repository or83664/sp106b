#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *mnemonic;
	char *bstring;
} dict_t;

static dict_t comp_Table[]={
    {"0","0101010"},
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"-D", "0001111"},
    {"-A", "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "010101"},
    {"M", "1110000"},
    {"!M", "1110001"},
    {"-M", "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"}
};

const char *Code_dest(const char *mnemonic) {
	if (strcmp(mnemonic,"null") == 0) {
		return "000";
	}
	
	else if (strcmp(mnemonic,"M") == 0) {
		return "001";
	}
	else if (strcmp(mnemonic,"D") == 0) {
		return "010";
	}
	else if (strcmp(mnemonic,"MD") == 0 ||strcmp(mnemonic,"DM") == 0) {
		return "011";
	}
	else if (strcmp(mnemonic,"A") == 0) {
		return "100";
	}
	else if (strcmp(mnemonic,"AM") == 0 ||strcmp(mnemonic,"MA") == 0) {
		return "101";
	}
	else if (strcmp(mnemonic,"AD") == 0 ||strcmp(mnemonic,"DA") == 0) {
		return "110";
	}
	else if (strcmp(mnemonic,"AMD") == 0 ||strcmp(mnemonic,"ADM") == 0
	        ||strcmp(mnemonic,"MAD") == 0||strcmp(mnemonic,"MDA") == 0
			 ||strcmp(mnemonic,"DMA") == 0||strcmp(mnemonic,"DAM") == 0) {
		return "111";
	}
	else{
		return 0;
	}	    
}

const char *Code_jump(const char *mnemonic){
	
	if (strcmp(mnemonic,"null") == 0) {
	   return "000";
	   }
    else if (strcmp(mnemonic,"JGT") == 0) {
		return "001";
	    }
	else if (strcmp(mnemonic,"JEQ") == 0) {
		return "010";
	    }
	else if (strcmp(mnemonic,"JGE") == 0) {
		return "011";
	    }   
	else if (strcmp(mnemonic,"JLT") == 0) {
		return "100";
	    } 
    else if (strcmp(mnemonic,"JNE") == 0) {
		return "101";
	    }
	else if (strcmp(mnemonic,"JLE") == 0) {
		return "110";
	    }    
	else if (strcmp(mnemonic,"JMP") == 0) {
		return "111";
	    }
	else{
		return 0;
	}
}

const char *Code_comp(const char *mnemonic){
	for (int i=0;i<sizeof(comp_Table)/sizeof(comp_Table[0]);i++)
    {
    	if (strcmp(mnemonic,comp_Table[i].mnemonic)==0)
    	{
    		return comp_Table[i].bstring;
		}
	}
	return NULL;
}
