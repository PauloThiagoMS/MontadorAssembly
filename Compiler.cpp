#include "lineClassfied.c"



int main(){
	FILE* pFile;
	pFile = fopen("source_code.asm","rw");
	if(pFile == NULL){
		printf("Erro ao abrir o arquivo!");
		exit(1);
	}else{
		system("del registradores.txt");
		system("copy registradoresReservados.txt registradores.txt");
		printf("preprocessamento...");
		preprocess(pFile);
		fclose(pFile);
		pFile = fopen("source_code-posprocess.asm", "r");
		printf(" ok\n");
		line* File = ReadFile(pFile);
		linesClassified(File);
		system("pause");
		printLine(File);
		
		//system("start 03subst.csv");
		system("pause");
		return 0;
	}
	return 0;
}
