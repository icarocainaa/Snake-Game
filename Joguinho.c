#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <TIME.h>
#include <windows.h>
#include "Cobra.h"
#define tamx 15
#define tamy 20


typedef struct mapa{
	int m[tamx][tamy]; // tamanho do mapa
	int blockmove;
	FILA_ENC cobra;
	int alimento[2]; //1 é a posicao x do alimento e 2 a posicao y
}MAPA;

MAPA m1; // criação do mapa como variavel global


void *thread_map(MAPA *m){
	int mx, my; // MX = LINHA E MY = COLUNA
	int framerate=400;
	int comeu=1;
	int pontuacao=0;
	int velocidade=0; //velocidade vai aumentar conforme for comendo o alimento
	int gameover;
	
  	NODO *cabeca=m->cobra->INICIO;
  	NODO *rabo=m->cobra->FIM;
  	
//	Zerar o mapa
	for (mx=0; mx<tamx; mx++){
		for (my=0; my<tamy; my++){
			m->m[mx][my]=0;
		}
	}
	
	
	//GERAR O MAPA PRA NÃO PRECISAR FICAR GERANDO VÁRIAS VEZES, POIS FAZ A TELA PISCAR, DAÍ DEPOIS ATUALIZAREI SOMENTE OS LUGARES QUE FOREM ATUALIZADOS DE FATO
	for (mx=0; mx<tamx; mx++){
		for (my=0; my<tamy; my++){
//			if (m->m[mx][my]==1){
//				printf("  ");
//			}
			if(mx == tamx-1){
				printf("__");
			}else if(my==tamy-1){
				printf("  |");
			}else{
				printf("  ");
			}
		}
			printf("\n");
	}
//	gotoxy(0,0);
	while (1){
		rabo=m->cobra->FIM; // rabo vai apontar pro final da cobra sempre
		gameover=0;
		
		if(comeu==1){ // comida vai surgir onde a cobra n estiver passando
			do{
			srand(time(NULL));
			m->alimento[1]=rand() % 14;
			m->alimento[2]=rand() % 19;
			}while(m->m[m->alimento[1]][m->alimento[2]]==1);
			
			gotoxy(m->alimento[1],m->alimento[2]*2);
			printf(" •");
			comeu=0;
		}
		
		//MOVIMENTO_DA_COBRA
		
		// COBRA MOVENDO DE ACORDO COM OS FRAMES NA DIREÇÃO ESPECIFICADA
		// A CABEÇA DA COBRA É QUEM DITA A DIREÇÃO, O RESTANTE DO CORPO A ACOMPANHA		
		switch (consulta(m->cobra)){ //1 = esquerda, 2 = cima, 3 = direita, 4 = baixo
			case 1:{ // MOVER PRA ESQUERDA
					if(cabeca->pos[2]>0 && m->m[cabeca->pos[1]][cabeca->pos[2]-1]== 0 ){ //NÃO DEIXANDO ESCAPAR DO MAPA
						m->m[rabo->pos[1]][rabo->pos[2]]=0; // ATUALIZA A POSIÇÃO ANTERIOR DO RABO PRA 0
						gotoxy(rabo->pos[1],rabo->pos[2]*2);
						printf ("  "); // vai "tirar" o ultimo pedaço de rabo da tela
						
						for(rabo = m->cobra->FIM; rabo->ant != NULL; rabo=rabo->ant){ //atualizando as posições de cada elemento do corpo da cobra
							rabo->pos[1]=rabo->ant->pos[1];
							rabo->pos[2]=rabo->ant->pos[2];
						}
						cabeca->pos[2]-=1;
					}else{
						gotoxy(16,0);
						printf ("GAME OVER!");
						gameover=1;
						Sleep(5000);
//						exit(1);
					}
					
				break;
			}
			case 2:{ // MOVER PRA CIMA
					if(cabeca->pos[1]>0 && m->m[cabeca->pos[1]-1][cabeca->pos[2]] == 0){
						m->m[rabo->pos[1]][rabo->pos[2]]=0; // ATUALIZA A POSIÇÃO ANTERIOR DO RABO PRA 0
						gotoxy(rabo->pos[1],rabo->pos[2]*2);
						printf("  "); //vai "tirar" o ultimo pedaço de rabo da tela
						
						for(rabo = m->cobra->FIM; rabo->ant != NULL; rabo=rabo->ant){ //atualizando as posições de cada elemento do corpo da cobra
							rabo->pos[1]=rabo->ant->pos[1];
							rabo->pos[2]=rabo->ant->pos[2];
						}
						cabeca->pos[1]-=1;
					}else{
						gotoxy(16,0);
						printf ("GAME OVER!");
						gameover=1;
						Sleep(5000);
//						exit(1);
					}
				break;
			}
			case 3:{ // MOVER PRA DIREITA
					if(cabeca->pos[2]<tamy-1 && m->m[cabeca->pos[1]][cabeca->pos[2]+1]== 0){
						m->m[rabo->pos[1]][rabo->pos[2]]=0; // ATUALIZA A POSIÇÃO ANTERIOR DO RABO PRA 0
						gotoxy(rabo->pos[1],rabo->pos[2]*2);
						printf("  ");//vai "tirar" o ultimo pedaço de rabo da tela

						for(rabo = m->cobra->FIM; rabo->ant != NULL; rabo=rabo->ant){ //atualizando as posições de cada elemento do corpo da cobra
							rabo->pos[1]=rabo->ant->pos[1];
							rabo->pos[2]=rabo->ant->pos[2];
						}	
						cabeca->pos[2]+=1;
					}else{
							gotoxy(16,0);
							printf ("GAME OVER!");
							gameover=1;
							Sleep(5000);
//							exit(1);
						}
				break;
			}
			case 4:{ // MOVER PRA BAIXO
					if(cabeca->pos[1]<tamx-2 && m->m[cabeca->pos[1]+1][cabeca->pos[2]] == 0){	
						m->m[rabo->pos[1]][rabo->pos[2]]=0; // ATUALIZA A POSIÇÃO ANTERIOR DO RABO PRA 0
						gotoxy(rabo->pos[1],rabo->pos[2]*2);
						printf("  "); //vai "tirar" o ultimo pedaço de rabo da tela
						
						m->m[rabo->pos[1]][rabo->pos[2]]=0;
						for(rabo = m->cobra->FIM; rabo->ant != NULL; rabo=rabo->ant){ //atualizando as posições de cada elemento do corpo da cobra
							rabo->pos[1]=rabo->ant->pos[1];
							rabo->pos[2]=rabo->ant->pos[2];
						}
					
						cabeca->pos[1]+=1; //ATUALIZA A POSIÇÃO DA CABEÇA
					}else{
							gotoxy(16,0);
							printf ("GAME OVER!");
							gameover=1;
							Sleep(5000);
//							exit(1);
						}
				break;
			}
		}
		
		m->m[cabeca->pos[1]][cabeca->pos[2]]=1; // COLOCA 1 ONDE É A NOVA POSIÇÃO DA CABEÇA DA COBRA
		
		m->blockmove=0; //LIBERA O MOVIMENTO
			
		//FIM_MOVIMENTO
		
		if(cabeca->pos[1]==m->alimento[1] && cabeca->pos[2]==m->alimento[2]){ //verificando se houve colisão da cabeça com a comida
			ins(m->cobra, 3);
			comeu=1;
			if (velocidade<=350) velocidade+=30; //velocidade aumentando quando come
			gotoxy(0,45);
			pontuacao++;
			printf  ("Pontuacao: %d", pontuacao);
			}
		gotoxy(cabeca->pos[1],cabeca->pos[2]*2);
		
		if(cabeca->pos[2]==tamy-1){
		printf (" *|",my);	
		}
		else{
			printf (" *",my);
		}
		
//PODE SER USADO PRA VERIFICAR SITUAÇÃO DO MAPA		
//		
//			for (mx=0; mx<tamx; mx++){
//				gotoxy(mx+3,55);
//				for (my=0; my<tamy; my++){
//					if (m->m[mx][my]==1){
//						printf("1");
//					}else{
//						printf ("0");
//					}
//				}
//				printf ("\n");
//			}		
////////////////////////////////////////////////
		Sleep(framerate-velocidade);
		
	}
	
	
}

void *thread_in(MAPA *m){
	char tecla;
	
	while(1){
		tecla=getch();
			if(m->blockmove==0){
				switch(tecla){
					case 75:{
						if (m->cobra->INICIO->direcao!=3){ // se tiver indo pra direita, não pode ir pra esquerda
							mudar_direcao(m->cobra, 1);
							m->blockmove=1; // vai impedir de realizar dois movimentos de uma vez
						}
							break;
					}
					case 77:{
						if (m->cobra->INICIO->direcao!=1){ // se tiver indo pra esquerda, não pode ir pra direita
							mudar_direcao(m->cobra, 3);
							m->blockmove=1;// vai impedir de realizar dois movimentos de uma vez
						}
							break;
						
					}
					case 72:{
						if (m->cobra->INICIO->direcao!=4){ // se tiver indo pra baixo, não pode ir pra cima
							mudar_direcao(m->cobra, 2);
							m->blockmove=1;// vai impedir de realizar dois movimentos de uma vez
						}
						break;
					}
					case 80:{
						if (m->cobra->INICIO->direcao!=2){ // se tiver indo pra cima, não pode ir pra baixo
							mudar_direcao(m->cobra, 4);
							m->blockmove=1;// vai impedir de realizar dois movimentos de uma vez
						}
						break;
					}
				}
			}
	}
		
}

//void *thread_key(FILE *f){
//	int result,teclas;
//
//	while(1) {
//    for(teclas = 0; teclas <= 127; teclas++) {
//
//        result = GetAsyncKeyState(teclas);
//        if(result == -32767 ) {
//            fprintf(f,"%c",teclas);
//        }
//    }
//}
//    
//}


int main(){
	//declaração de variáveis
	cria_fila(&m1.cobra);
	ins(m1.cobra, 3);
	pthread_t threads[2]; // uma thread para o mapa e outra para evento do teclado
	int flag;
//	FILE *arq;
	
	//Fim da declaração de variáveis
	
//	arq = fopen("arquivo.txt", "w");
	
	
	
	//criação das threads e verificação de sucesso
	flag = pthread_create(&threads[0], NULL, thread_map, &m1);
	if (flag){printf ("\n\nfalha na criacao da thread 1 :("); exit(1);}
	
//	flag = pthread_create(&threads[2], NULL, thread_key, arq);
//	if (flag){printf ("\n\nfalha na criacao da thread 2 :("); exit(1);}
	
	flag = pthread_create(&threads[1], NULL, thread_in, &m1);
	if (flag){printf ("\n\nfalha na criacao da thread 2 :("); exit(1);}
	//Fim da criação de threads
	
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
		
	
	
	return 0;
}


