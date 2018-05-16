#include "lineClassfied.c"



int main(){
	FILE* pFile;
	pFile = fopen("source_code.asm","rw");
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}else{
		printf("preprocessamento...");
		preprocess(pFile);
		fclose(pFile);
		pFile = fopen("03subst.txt", "r");
		printf(" ok\n");
		line* File = ReadFile(pFile);
		linesClassified(File);
		system("pause");
		printLine(File);
		
		//system("start 03subst.csv");
		return 0;
	}
	return 0;
}
