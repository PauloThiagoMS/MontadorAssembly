#include <stdio.h>
#include <string.h>
#include "Files.c"
int cblocks = 0;


int isDigits(char c){
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isAlphas(char c){
	if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}

int isAlphaHexs(char c){
	if((c >= 'a' && c <= 'f')||(c >= 'A' && c <= 'F')||(isDigits(c)))
		return 1;
	else
		return 0;
}

int isBits(char c){
	if(c == '0' || c == '1')
		return 1;
	else
		return 0;
}

int isNumeric(char c){
	if(c < 58 && c > 47)
		return 1;
	return 0;
}


int isNums(char *word){
	char *c = word;	
	while(*c != '\0'){
		if(!isDigits(*c))
			return 0;
		c++;
	}
	return 1;
}

int isHexs(char *word){
	char *c = word;	
	if(*c == 'H'){
		c++;
		if(*c == '\''){
			do{
				c++;
			} while(isDigits(*c) || isAlphaHexs(*c));
			if(*c == '\''){
				c++;
				if(*c == '\0'){
					return 1;
				}
			}
		}
		return 0;
	}
	else if(*c == '0'){
		c++;
		if(*c == 'X' || *c == 'x' ){
			do{
				c++;
			} while(isDigits(*c) || isAlphaHexs(*c));
			if(*c == '\0'){
				return 1; 
			}
		}
	}
	return 0;
}

int isBin(char *word){
	char *c = word;
	if(*c != 'B')
		return 0;
	c++;
	if(*c == '\''){
		do{
			c++;
		} while(isBits(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c == '\0')
			return 1;
	}
	return 0;
}

int isDec(char *word){
	char *c = word;
	if(*c != 'D')
		return 0;
	c++;
	if(*c == '\''){
		do{
			c++;
		} while(isDigits(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c != '\0')
			return 0;
	}
	return 1;
}

int checkFile(char *word, char *NameFile){
	FILE* fi;
	fi = fopen(NameFile,"r");
	if(fi && strlen(word)>0){
		int cont = 0; 
		char str[255];
		char wordx[255];
		strcpy(wordx,word);
		strupr(wordx);
		while(!feof(fi)){
			cont++;
			fgets(str,255,fi);
			if(str[0] != ';'){
				str[strlen(str)-1] = '\0';
				if(strcmp(str,wordx)==0 ){
					fclose(fi);
					return cont;
				}
			}
		}
		fclose(fi);
		return 0;
	}else{
		return -1;
	}
	
}

int configAmbiente(char *word){
	return checkFile(word,"ConfigAmbiente.txt");
}

int reservedRegis(char *word){
	return checkFile(word,"registradores.txt");
}

int reservedInst(char *word){
	return checkFile(word,"instrucoesreservadas.txt");
}

int isIdentification(char* word){
	if(word != NULL){
		if(isAlphas(word[0])){
			int x = 1;
			while(word[x] != '\0'){
				if(!isDigits(word[x]) && !isAlphas(word[x])){
					return 0;
				}
				x++;
			}
			return 1;
		}
	}
	return 0;
}

int isLiteral(char *word){
	if(isNums(word) || isHexs(word)|| isDec(word) || isBin(word)){
		return 1;
	}
	return 0;
}


int isSeparate(char *words){
	if((strlen(words)==1) && ((words[0] == ',') )){
		return 1;
	}
	return 0;
}

int isDescLabel(char *words){
	if((strlen(words)==1) && (words[0] == ':')){
		return 1;
	}
	return 0;
}

int isLabel(word *word){	
	if(word->fist){
		if(word->NEXT != NULL){
			char * teste = word->NEXT->content;
			if(isDescLabel(teste)){
				return 1;
			}else{
				
			}
		}
	}
	return 0;
}



int ident2Register(word* words){
	if(cblocks){
		words->tipe =  3;
		char *str = strupr(words->content);
		FILE* regs = fopen("registradores.txt", "rw");
		char str2[255] = "";
		sprintf(str2,"echo %s >>registradores.txt",str);
		system(str2);
	
		return 1;
	}else{
		return 0;
	}
}

int wordClassified(word* words){
	if(words != NULL){
		if(strlen(words->content)==0){
			words->tipe = 0;
			return 1;
		}else{
			if(isSeparate(words->content)){
				words->tipe = 6;
				return 1;
			}else{
				if(isDescLabel(words->content)){
					words->tipe = 7;
				return 1;
				}else{
					if(isLiteral(words->content)){
						words->tipe =  4;
						return 1;
					}else{
						int id = configAmbiente(words->content);
						if(id >0){
							words->tipe =  1;
							words->id = id;
							return 1;
						}else{
							id = reservedRegis(words->content);
							if(id >0){
								words->tipe =  3;
								words->id = id;
								return 1;
							}else{
								id = reservedInst(words->content);
								if(id >0){
									words->tipe =  2;
									words->id = id;
									if(id == 30){
										cblocks = 1;	
									}
									if(id == 5){
										cblocks = 0;	
									}
									return 1;
								}else{
									if(isIdentification(words->content)){
										words->tipe =  5;
										ident2Register(words);
											
										return 1;
									}else{
										//printf("nao foi possivel identificar: [%s] !\n",words->content);
										//system("pause");
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

void wordsClassied(word* words){
	if(words != NULL){
		wordClassified(words);
		wordsClassied(words->NEXT);
	}
} 


