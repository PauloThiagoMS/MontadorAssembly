#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct _word {
	int fist;
	int tipe;
	int id;	
	char content[255];
	struct _word* NEXT;
}word;

//
typedef struct _line {
	int tipe;
	int lineCont;
	int wordCont;
	word* words;
	struct _line* NEXT;
}line;

//Cria a estrutura da linha
line* create_line( line* NEXT){
	line *new_line = (line*) malloc (sizeof(line));
	new_line->NEXT = NEXT;
	new_line->lineCont = 0;
	new_line->tipe = 0;
	new_line->wordCont = 0;
	return new_line;
}

word* create_word(char content[255], word* NEXT){
	word *new_word = (word*) malloc (sizeof(word));
	new_word->tipe = 0;
	new_word->id = 0;
	new_word->fist = 0;
	new_word->NEXT = NEXT;
	strcpy(new_word->content,content);
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
	return cont;
}

char* getword(int cont, char string[1024]){
	char strin[255] = "";
	int c = 0;
	if(cont > 0){
		while (cont > 0){
			if(string[c] == ' '){
				cont --;
			}
			c++;
		}
	}
	int x = 0;
	while(string[c] != ' ' && string[c] != '\0'){
		strin[x] = string[c];
		c++;
		x++;
	}
	strin[x] = '\0';
	return strin;
}

word* setword(int jumps, char string[1024],int Limit){
	word* new_word = NULL;
	if(jumps < Limit){
		new_word = create_word(getword(jumps,string),setword(jumps+1,string,Limit));
		if(jumps == 0){
			new_word->fist = 1;
		}
	}
	return new_word;
}

//Retorna um array de strings com as palavras de cada linha; 
void getwords(char string[1024], line* line){
	line->wordCont = charcont(string,' ');
	line->words = setword(0,string,line->wordCont);
}

void wordContent(word* words){
	if(words != NULL){
		if(words->fist){
				printf("->");
		}
		printf("[%s](%d)",words->content,words->tipe);
		wordContent(words->NEXT);	
	}else{
		printf("\n");
	}
}


void printLine(line* line){
	if(line != NULL){
		printf("%3d",line->lineCont);
		wordContent(line->words);
		printLine(line->NEXT);
	}
}

void printLine1(line* line){
	if(line != NULL){
		printf("%3d",line->lineCont);
		wordContent(line->words);
	}
}

//Le todas as linhas do arquivo
line* ReadLine(line* LastLine,FILE* Finput,int lineConts){
	line* new_line = NULL;
	if(!feof(Finput)){
		char string[1024];
		fgets(string,1024,Finput);
		string[strlen(string)-1] = '\0';
		new_line = create_line(ReadLine(new_line,Finput,lineConts+1));
		getwords(string,new_line);
		new_line->lineCont = lineConts;
	}
	return new_line;
}

//Retor a primeira linha da arvore de linhas do arquivo
line* ReadFile(FILE* Finput){
	if(Finput == NULL){
		printf("Erro ao abrir o arquivo!");
		return NULL;
	}else{
		line* new_line;
		new_line = ReadLine(new_line,Finput,1);
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
		}else{
			if(c>0){
				fprintf(outputFile, "%c" , c);	
			}
		}
	}
	fclose(inputFile);
	fclose(outputFile);
	inputFile = fopen("01nocoment.txt", "r");
	outputFile = fopen("02notabspace.txt", "w");

	while(!feof(inputFile)){					//substituição de caracteres 	
		c = fgetc(inputFile);							
		if(c>0){
			if(c == ','){
				fprintf(outputFile, "%s", " , ");
			}else{
				if(c == '\n' || c == ':'){
						fprintf(outputFile, " ");
				}
				fprintf(outputFile, "%c" , c);	
			}
		}	
	}
	fclose(inputFile);	
	fclose(outputFile);
	inputFile = fopen("02notabspace.txt", "r");
	system("del /f /q source_code-posprocess.asm");
	outputFile = fopen("source_code-posprocess.asm", "w");
		
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
	
	fclose(inputFile);
	fclose(outputFile);
	
	system("del /f /q 01nocoment.txt");
	system("del /f /q 02notabspace.txt");

	//system("pause");
		 	
	//return outputFile;
	fclose(outputFile);
}


