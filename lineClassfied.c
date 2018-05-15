#include "wordClassfied.c"

int lineClassified(line* line){
	word* words = line->words;
	if( words->tipe != 0){
		if(words->tipe == 5){
			if(words->NEXT->tipe == 7){
				char* ii = "Labels.txt";
				int id = checkFile(words->content,ii);
				if(id == 0){
					//addLabel(words);
					line->wordCont--;
					word* fre = words->NEXT;
					words->NEXT = fre->NEXT;
					free(fre);
				}else{
					printf("linha %d :Erro! Label previamente declarado na linha: %d.\n",line->lineCont,id);
					system("pause");
					exit(1);
				}
			}else{
				printf("linha %d :Erro! Declaracao incorreta de Label\'s ,Espera-se um (\":\") apos: (%s).\n",line->lineCont,words->NEXT->content);
				system("pause");
				exit(1);
			}	
		}else{
			if(words->tipe = 1){
				return 1;
			}else{
				printf("linha %d :Erro! Declaracao incorreta de Label\'s ,Espera-se um identificador no lugar de: (%s).\n",line->lineCont,words->content);
				system("pause");
				exit(1);
			}
		}	
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
									printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo Literal.\n",line->lineCont,words->content);
									system("pause");
									exit(1);
								}
							}
							if(words->id < 61){
								if(words->NEXT->tipe == 3){
									return 1;	
								}else{
									printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo registrador.\n",line->lineCont,words->content);
									system("pause");
									exit(1);
								}
							}
							if(words->NEXT->tipe == 5){
								return 1;	
							}else{
								printf("linha %d :Erro! O comando: (%s) Requer um parametros do tipo identificador.\n",line->lineCont,words->content);
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
									if(words->NEXT->tipe == 3 && words->NEXT->NEXT->NEXT->tipe == 4){
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
	
	
	
	
}


void linesClassified(line* lines){
	if(lines != NULL){
		wordsClassied(lines->words);
		lineClassified(lines);
		linesClassified(lines->NEXT);
	}
}


