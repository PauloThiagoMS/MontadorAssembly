#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// GLOBAL VARIABLES: oi
char instrucao[40][255];
char registrador[260][255];

typedef struct tok {
	int id;
	char tipo[50];
	char word[255];
	struct tok *next;
}token;


token* create_token(int id, char *tipo, char *word){
	token *new_token = (token*) malloc (sizeof(token));
	new_token->id = id;
	strcpy(new_token->tipo, tipo);
	strcpy(new_token->word, word);
	new_token->next = NULL;
	return new_token;
}

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
	if((c >= 'a' && c <= 'f')||(c >= 'A' && c <= 'F')||(isDigt(c)))
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

int isNums(char *word){
	char *c = word;	
	while(*c != '\0'){
		if(!isDigit(*c))
			return 0;
		c++;
	}
	return 1;
}

int isHexs(char *word){
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

int isBin(char *word){
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

int isDec(char *word){
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

//<<<<<<< HEAD
int isNumeric(char c){
	if(c < 58 && c > 47)
		return 1;
	return 0;
}

int reservedRegis(char *word){
	FILE* fi;
	fi = fopen("registradoresreservados.txt","r");
	int cont = 0; 
	char str[255];
	while(!feof(fi)){
		cont++;
		fgets(str,255,fi);
		if(strcmp(str,word)){
			fclose(fi);
			return cont;
		}		
	}
	fclose(fi);
	return 0;
}

int reservedInst(char *word){
	FILE* fi;
	fi = fopen("instrucoesreservadas.txt","r");
	int cont = 0;
	char str[255];
	while(!feof(fi)){
		cont++;
		fgets(str,255,fi);
		if(strcmp(str,word)){
			fclose(fi);
			return cont;
		}
	}
	fclose(fi);
	return 0;
}

/*
char getWords(char str[1024]){
	char linha[4][255];
	int c=0;// ponteiro do caracter na linha
	int x=0;// ponteiro da palavra 
	int y=0;// ponteiro do caracter na palavra
	while(str[c]!= '\n'){
		linha[x][y] = str[c];
		c++;
		y++;
		if((str[c]!= ' ')||(str[c]!= ',')){
			x++;
			y=0;
		}	
	}
	return linha;
}

*/

int isLinha(char str[1024]){
	char cAtual = NULL;
	char cProx = NULL;
	char word[255];
	int c=0;
	int x=0;
	while(cAtual != '\n'){
		word[x]= cAtual;
		cAtual = cProx;
		cProx = str[c];
		c++;
		x++;
		if(cProx == ' ' ){
			word[x+1]='\0';
			x=0;
			if(cAtual == ':'){
				sendC1(word);
			}else{
				sendC2(word);
			}
		}
	}
}

void preprocess(FILE *inputFile){
	int c;
	FILE * outputFile = fopen("preprocessed.asm", "w");
	if(outputFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}
	while(!feof(inputFile)){					
		c = fgetc(inputFile);							
		if(c == ';'){							//Remover os comentarios
			while(c != '\n'){
				c = fgetc(inputFile);
			}
			fseek(inputFile, -1, SEEK_CUR);
		}
		if(c == ',')
			fprintf(outputFile, "%s", " , ");
		if(c == ' ' || c == '\t' ){				//Remover espaÃ§os e tabs repetidos
			fprintf(outputFile, "%c" , '*');
			while(c == ' ' || c == '\t' ){
				c = fgetc(inputFile);
			}
			fseek(inputFile, -1, SEEK_CUR);
		}
		if(c>0){
			fprintf(outputFile, "%c" , c);	
		}
	}	
	fclose(outputFile);

	//printf("//Remover separando 1 e 2 operadores\n");

	
}

void novoPreprocess(FILE *inputFile){
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
		if(c == ' ' || c == '\t' ){				//Remover espaÃ§os e tabs repetidos por um unico ;
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
	outputFile = fopen("preprocessfile.csv", "w");
		
	while(!feof(inputFile)){					//substitui��o de caracteres 
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
	FILE *pFile = fopen("source_code.asm","r");
	novoPreprocess(pFile);
	fclose(pFile);
	
	pFile = fopen("preprocessfile.csv","r");
	system("pause");
	

	
	
	
	/*
	
	
	token *symbolTable = create_token(0, "SymbolTable", "Raiz");

	FILE *pFile = fopen("instrucoesreservadas.txt","r");
	
	int i;
	char word[255];
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}

	for(i=0;!feof(pFile);i++){
		fgets(word,255,pFile);
		word[strlen(word)-1] = '\0';
		if(!feof(pFile))
			strcpy(instrucao[i],word);
	}	
	fclose(pFile);
	instrucao[i][0]= EOF;
	
	// imprime as instrucoes reservadas para verificacao
	//for(i=0; instrucao[i][0]!= EOF; i++)
	//	printf("%s\n",instrucao[i]);

	pFile = fopen("registradoresreservados.txt","r");
	
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}

	rewind(pFile);
	for(i=0;!feof(pFile);i++){
		fgets(word,255,pFile);
		word[strlen(word)-1] = '\0';
		if(!feof(pFile))
			strcpy(registrador[i],word);
	}
	fclose(pFile);
	registrador[i][0]= EOF;
	
	// imprime os registradores reservados para verificacao
	//for(i=0; registrador[i][0]!= EOF; i++)
	//	printf("%s\n",registrador[i]);
	
	pFile = fopen("codigofonte.asm","r");
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}
	preprocess(pFile);
	fclose(pFile);

	token *aux = symbolTable;
	insert_token("MOVF", symbolTable);
	insert_token("TRISA", symbolTable);
	do{
		printf("\nID: %d  TIPO: %s  PALAVRA: %s", aux->id, aux->tipo, aux->word);
		aux = aux->next;
	} while(aux != NULL);
	
	char teste[255] = "D'0010'";
	if(isDec(teste))
		printf("\n %s Eh um decimal", teste);
	else
		printf("\n %s Nao eh um decimal", teste);

	*/

	return 0;
}

