#include "wordClassfied.c"

int labelClassfied(line* lines){
	word* words = lines->words;
	if(words->tipe == 5){
	return 1;
		/*if(lines->wordCont > 1){
			if(words->NEXT->tipe == 7){
				char* ii = "Labels.txt";
				//int id = checkFile(words->content,ii);
				int id = 0;
				if(id == 0){
					//addLabel(words);
					lines->wordCont--;
					word* fre = words->NEXT;
					words->NEXT = fre->NEXT;
					free(fre);
					return 1;				
				}else{
					printf("linha %d :Erro! Label previamente declarado na linha: %d.\n",lines->lineCont,id);
					system("pause");
					exit(1);
					return 0;
				}
			}
			
		}
		*/
		printf("linha %d :Erro! Declaracao incorreta de Label\'s ,Espera-se um (\":\") apos: (%s).\n",lines->lineCont,words->NEXT->content);
		system("pause");
		exit(1);
	}else{
		if(words->tipe == 1){
			return 1;
		}else{
			printf("linha %d :Erro! Declaracao incorreta de Label\'s ,Espera-se um identificador no lugar de: (%s).\n",lines->lineCont,words->content);
			system("pause");
			exit(1);
		}
	}
}

	
int check1Param(line* lines){
	word* words = lines->words->NEXT;
	if(words->NEXT != NULL){
		if(words->id < 40){
			if(words->NEXT->tipe != 4){
				printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo Literal no lugar de: (%s).\n",lines->lineCont,words->content,words->NEXT->content);
				printLine1(lines);
				system("pause");
				exit(1);
			}
			return 1;
		}
		if(words->id < 60){
			if(words->NEXT->tipe != 3){
				printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo registrador no lugar de: (%s).\n",lines->lineCont,words->content,words->NEXT->content);
				printLine1(lines);
				system("pause");
				exit(1);
			}
			return 1;
		}
		if(words->NEXT->tipe != 5){
				printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo identificador no lugar de: (%s).\n",lines->lineCont,words->content,words->NEXT->content);
				printLine1(lines);
				system("pause");
				exit(1);
		}
		return 1;
	}
	printf("Erro! linha: %d.  Parametro nulo apos: (%s).\n",lines->lineCont,words->content);
	system("pause");
	exit(1);	
}

int check2Param(line* lines){
	word* words = lines->words->NEXT;
	if(words->NEXT != NULL ){
		if(words->NEXT->tipe != 3){
			printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo registrador no lugar de: (%s).\n",lines->lineCont,words->content,words->NEXT->content);
			printLine1(lines);
			system("pause");
			exit(1);
		}
		if(words->NEXT->NEXT != NULL ){
			if(words->NEXT->NEXT->tipe != 6){
				printf("linha %d :Erro! O comando: (%s) Requer um (\',\') apos: %s.\n",lines->lineCont,words->content,words->NEXT->content);
				printLine1(lines);
				system("pause");
				exit(1);
			}
			if(words->NEXT->NEXT->NEXT != NULL ){
				if(words->id <100 ){
					if(words->NEXT->NEXT->NEXT->tipe != 3){
						printf("linha %d :Erro! O comando: (%s) Requer dois parametros do tipo registrador.\n",lines->lineCont,words->content);
						printLine1(lines);
						system("pause");
						exit(1);
					}else{
						return 1;
					}
				}else{
					if(words->NEXT->NEXT->NEXT->tipe != 4 && words->NEXT->NEXT->NEXT->tipe != 3 ){
						printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo registrador e outro do tipo (BitLiteral ou BitRegistrador).\n",lines->lineCont,words->content);
						printLine1(lines);
						system("pause");
						exit(1);
					}else{
						return 1;
					}
				}
			}
		}
	}
	printf("Erro! linha: %d.  Parametro nulo apos: (%s).\n",lines->lineCont,words->content);
	system("pause");
	exit(1);	
}


	
int registClassfied(line* lines){
	word* words = lines->words->NEXT;
	if(words->id < 20){										//Instruções sem operadores
		if(lines->wordCont != 2){
			printf("Erro! linha: %d.  O comando: (%s) Nao aceita parametros.\n",lines->lineCont,words->content);
			printLine1(lines);
			system("pause");
			exit(1);
			return 0;
		}else{
			return 1;
		}
	}else{
		if(words->id < 80){									//Instruções com um operador
			if(lines->wordCont != 3 ){
				printf("linha %d :Erro! O comando: (%s) Requer um parametro.\n",lines->lineCont,words->content);
				printLine1(lines);
				system("pause");
				exit(1);
				return 0;
			}else{
				check1Param(lines);
				return 1;
			}	
		}else{												//Instruções com dois operadores
			if(lines->wordCont != 5){
				printf("linha %d :Erro! O comando: (%s) Requer dois parametros.\n",lines->lineCont,lines->words->content);
				printLine1(lines);
				system("pause");
				exit(1);
				return 0;
			}else{
				check2Param(lines);
				return 1;
			}
		}
	}
}	
		
	
	
int lineClassified(line* lines){
	word* words = lines->words;
	if( words->tipe != 0){
		labelClassfied(lines);
	}
	if(words->NEXT != NULL){
		words = words->NEXT;
		switch (words->tipe){
			case (0):{
				return 1;
				break;
			}
			case (1):{
				return 1;
				break;
			}
			case (2):{
				registClassfied(lines);
				return 1;
				break;
			}
			
			case (3):{
				if(!ident2Register(words)){
					printf("Erro! Linha: %d. Declaração incorreta de registrador (%s)\n",lines->lineCont,words->content);
					printLine1(lines);
					system("pause");
					exit(1);
				}
				return 1;
				break;
			}
			default:{
				printf("Erro! Linha: %d. Tipo Incompativel para esse posicao (%s)\n",lines->lineCont,words->content);
				printLine1(lines);
				system("pause");
				exit(1);
				return 0;
				break;
			}
		}
	}
}

		
		/*
		
		
			
	}
	if(words->NEXT != NULL){
	words = words->NEXT;
		if( words->tipe != 0){
			if( words->tipe == 1){
				return 1;
			}else{
				if( words->tipe == 2){
					line->tipe = 1;
					if(words->id < 81){
						if(words->id < 21){
							if(line->wordCont = 2){
								return 1;
							}else{
									printf("linha %d :Erro! O comando: (%s) Nao aceita parametros.\n",line->lineCont,words->content);
									system("pause");
									exit(1);
							}
						}
						if(line->wordCont = 3){
							if(words->id < 41){
								if(words->NEXT->tipe == 4){
									return 1;	
								}else{
									printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo Literal no lugar de: (%s).\n",line->lineCont,words->content,words->NEXT->content);
									system("pause");
									exit(1);
								}
							}
							if(words->id < 61){
								if(words->NEXT->tipe == 3){
									return 1;	
								}else{
									printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo registrador no lugar de: (%s).\n",line->lineCont,words->content,words->NEXT->content);
									system("pause");
									exit(1);
								}
							}
							if(words->NEXT->tipe == 5){
								return 1;	
							}else{
								printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo identificador no lugar de: (%s).\n",line->lineCont,words->content,words->NEXT->content);
								system("pause");
								exit(1);
							}
						}else{
							printf("linha %d :Erro! O comando: (%s) Requer um parametro.\n",line->lineCont,words->content);
							system("pause");
							exit(1);
						}
					}else{
						if(line->wordCont = 5){
							if(words->NEXT->NEXT->tipe == 6){
								
								if(words->id < 101){
									if(words->NEXT->tipe == 3 && words->NEXT->NEXT->NEXT->tipe == 3){
										return 1;	
									}else{
										printf("linha %d :Erro! O comando: (%s) Requer dois parametros do tipo registrador.\n",line->lineCont,words->content);
										system("pause");
										exit(1);
									}
								}else{
									if(words->NEXT->tipe == 3 && (words->NEXT->NEXT->NEXT->tipe == 3 || words->NEXT->NEXT->NEXT->tipe == 4)){
										return 1;	
									}else{
										printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo registrador e outro do tipo literal.\n",line->lineCont,words->content);
										system("pause");
										exit(1);
									}
								}
							}else{
								printf("linha %d :Erro! O comando: (%s) Requer um (\',\') apos: %s.\n",line->lineCont,words->content,words->NEXT->content);
								system("pause");
								exit(1);	
							}
						}else{
							printf("linha %d :Erro! O comando: (%s) Requer dois parametros.\n",line->lineCont,line->words->content);
							system("pause");
							exit(1);
						}
						
					}
						
						
						
				}
			}
		}
	}
	
	
	*/
	



void linesClassified(line* lines){
	if(lines != NULL){
		if(lines->words != NULL){
			wordsClassied(lines->words);
			lineClassified(lines);
			system("cls");
			printf("%3d ok\n",lines->lineCont);
			linesClassified(lines->NEXT);
		}else{
			system("cls");
			printf("linesClassfied Complete!\n");
		}
	}
}


