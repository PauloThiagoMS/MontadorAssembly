#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct _word {
	int tipe;	
	char content[255];
	_word* NEXT;
}word;

//
typedef struct _line {
	int wordCont;
	word* words;
	_line* NEXT;
}line;

//Cria a estrutura da linha
line* create_line(word* words, line* NEXT){
	line *new_line = (line*) malloc (sizeof(line));
	new_line->words = words;
	new_line->NEXT = NEXT;
	return new_line;
}

word* create_word(char content[255], word* NEXT){
	word *new_word = (word*) malloc (sizeof(word));
	new_word->tipe = 0;
	//strcpy(new_word->content,content);
	new_word->NEXT = NEXT;
	return new_word;
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
	line->wordCont = charcont(string,' ')+1;
	if(line->wordCont > 0){
		int cont = 0;
		while(cont < (line->wordCont)){
			
			cont++;
		}
	}		
}

char* getword(int cont,char string[1024]){
	if(cont > 0){
		char strin[255];
		sscanf(string,"%s ",strin);
		//printf("%s",strin);
		/*
		char c;
		while(cont>0){
			c = gets(string);
			if(c == ' '){
				cont--;
			}
		}
		c = gets(string);
		while(c != ' ' && c != '\n'){
			string[]
		}
		*/
		return strin;
	}else{
		return NULL;
	}
}



//Le todas as linhas do arquivo
line* ReadLine(line* LastLine,FILE* Finput){
	if(!feof(Finput)){
		char string[1024];
		fgets(string,1024,Finput);
		printf("%s\n",getword(1,string));
		
		line* new_line;
		//getwords(string,new_line);
		new_line = create_line(create_word(string,NULL),ReadLine(new_line,Finput));
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

	while(!feof(inputFile)){					//substituição de caracteres 	
		c = fgetc(inputFile);							
		if(c == ','){
				fprintf(outputFile, "%s", " , ");
		}else{
			if(c == '\n'){
					fprintf(outputFile, "%s", " \n");
			}else{
				if(c>0){
						fprintf(outputFile, "%c" , c);	
				}
			}
		}
	}	
	fclose(outputFile);
	inputFile = fopen("02notabspace.txt", "r");
	outputFile = fopen("03subst.csv", "w");
		
	while(!feof(inputFile)){					
		c = fgetc(inputFile);							
		if(c == ' ' || c == '\t' ){				//Remover espaÃƒÂ§os e tabs repetidos por um unico 
				fprintf(outputFile, "%c" , ' ');
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
		//system("start 03subst.csv");
	}return 0;
}
