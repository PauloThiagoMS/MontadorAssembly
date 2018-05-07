#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct _word {
	int tipe;	
	char content[255];
}word;

//
typedef struct _line {
	int wordCont;
	word* words;
	_line* NEXT;
}line;

//Cria a estrutura da linha
line* create_line(line* NEXT){
	line *new_line = (line*) malloc (sizeof(line));
	new_line->words = NULL;
	new_line->NEXT = NEXT;
	return new_line;
}

//retorna a quantidade de caracteres contidos na string
int charcont(char string[1024], char Caracter){
	int cont = 0, x = 0; 
	while(string[x] != '\0'){
		if(string[x] == Caracter){
			cont++;
		}
		x++;
	}
	//printf("possui %d palavras.\n",cont);
	return cont;
}

//Retorna um array de strings com as palavras de cada linha; 
void getwords(char string[1024], line* line){
	line->wordCont = charcont(string,';');
	if(line->wordCont > 0){
		line->words = (word*) malloc(sizeof(word)*line->wordCont);
		int cont = 0;
		int charloc = 0;
		while(cont < line->wordCont){
			int charw = 0;
			while(string[charloc] != ';'){
				word* lword= (line->words);
				char* lcontent = lword->content;
				lcontent[charw] = string[charloc];
				charw++;
				charloc++;
			}
			system("pause");
			printf((line->words)->content);
			system("pause");
		
			charloc++;
		}
	}		
}

//Le todas as linhas do arquivo
line* ReadLine(line* LastLine,FILE* Finput){
	if(!feof(Finput)){
		char string[1024];
		fgets(string,1024,Finput);
		//printf(string);
		line* new_line;
		getwords(string,new_line);
		new_line = create_line(ReadLine(new_line,Finput));
		return new_line;
		
	}else{
		return NULL;
	}
}

//Retor a primeira linha da arvore de linhas do arquivo
line* ReadFile(FILE* Finput){
	if(Finput == NULL){
		printf("Erro ao abrir o arquivo!");
		return NULL;
	}else{
		line* new_line;
		new_line = ReadLine(new_line,Finput);
		return new_line;
	}
}


void comentarios(){

/*

_Bool isDigit(char c){
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isAlpha(char c){
	if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}
int isAlphaHex(char c){
	if((c >= 'a' && c <= 'f')||(c >= 'A' && c <= 'F')||(isDigt(c)))
		return 1;
	else
		return 0;
}

int isBit(char c){
	if(c == '0' || c == '1')
		return 1;
	else
		return 0;
}

_Bool isNum(char *word){
	char *c = word;	
	while(*c != '\0'){
		if(!isDigit(*c))
			return 0;
		c++;
	}
	return 1;
}


_Bool isHex(char *word){
	char *c = word;
	if(*c == 'H')
		c++;
	if(*c == '\''){
		do{
			c++;
		} while(isDigit(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c != '\0')
			return 0;
		return 1;
	}
	else if(*c != '0')
		return 0;
	c++;
	if(*c != 'X')
		return 0;
	do{
		c++;
	} while(isDigit(*c) || isAlphaHex(*c));
	if(*c != '\0')
		return 0; 
	
	return 1;
}

_Bool isBin(char *word){
	char *c = word;
	if(*c != 'B')
		return 0;
	c++;
	if(*c == '\''){
		do{
			c++;
		} while(isBit(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c != '\0')
			return 0;
	}
	return 1;
}

_Bool isDec(char *word){
	char *c = word;
	if(*c != 'D')
		return 0;
	c++;
	if(*c == '\''){
		do{
			c++;
		} while(isDigit(*c));
		if(*c != '\'')
			return 0;
		c++;
		if(*c != '\0')
			return 0;
	}
	return 1;
}

void insert_token(char *word, token *symbolTable){
	int i;
	token *aux = symbolTable;

// Implementar Se BNF == Identificador
// Bloco para buscar por RESERVADOS

	for(i=0; instrucao[i][0]!= EOF; i++){
		if(strcmp(word, instrucao[i]) == 0){
			while(aux->next != NULL)
				aux = aux->next;			
			aux->next = create_token(100 + i, "Instrucao", word);
			return;
		}
	}
	for(i=0; registrador[i][0]!= EOF; i++)
		if(strcmp(word, registrador[i]) == 0){
			while(aux->next != NULL)
				aux = aux->next;			
			aux->next = create_token(200 + i, "Registrador", word);
			return;
		}
// FIM DO BLOCO PALAVRAS RESERVADAS
/*
	
	Se o Identificador nao for palavra reservada, sera uma label
*/

}

//pre processamento
void preprocess(FILE *inputFile){
	if(inputFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}
	FILE * outputFile = fopen("01nocoment.txt", "w");
	int c;
	while(!feof(inputFile)){					
		c = fgetc(inputFile);							
		if(c == ';'){							//Remover os comentarios
			while(c != '\n' && c >0){
				c = fgetc(inputFile);
			}
			fprintf(outputFile, "%c" , c);
		}
		if(c>0){
						fprintf(outputFile, "%c" , c);	
				}
	}
	fclose(outputFile);
	inputFile = fopen("01nocoment.txt", "r");
	outputFile = fopen("02notabspace.txt", "w");
	
	while(!feof(inputFile)){					
		c = fgetc(inputFile);							
		if(c == ' ' || c == '\t' ){				//Remover espaÃƒÂ§os e tabs repetidos por um unico ;
				fprintf(outputFile, "%c" , ';');
				while(c == ' ' || c == '\t'  ){
					c = fgetc(inputFile);
				}
				fprintf(outputFile, "%c" , c);
		}else {
			if(c>0){
						fprintf(outputFile, "%c" , c);	
				}
		}
	}
	fclose(outputFile);
	inputFile = fopen("02notabspace.txt", "r");
	outputFile = fopen("03subst.csv", "w");
		
	while(!feof(inputFile)){					//substituição de caracteres 
		c = fgetc(inputFile);							
		if(c == ','){
				fprintf(outputFile, "%s", ";,;");
		}else{
			if(c == '\n'){
					fprintf(outputFile, "%s", ";\n");
			}else{
				if(c>0){
						fprintf(outputFile, "%c" , c);	
				}
			}
		}
	}		 	
	//return outputFile;
	fclose(outputFile);
}

int main(){
	FILE* pFile;
	pFile = fopen("source_code.asm","r");
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}else{
		printf("preprocessamento...");
		preprocess(pFile);
		fclose(pFile);
		pFile = fopen("03subst.csv", "r");
		printf(" ok\n");
		
		
		line* File = ReadFile(pFile);
		system("start 03subst.csv");
	}return 0;
}
