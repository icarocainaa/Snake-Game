#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

typedef struct nodo{
	int direcao; //só vai ser usado na cabeça da cobra
	int pos[2]; //pos[1]=x e pos[2]=y
	struct nodo *next;
	struct nodo *ant;
}NODO;

void gotoxy(int x, int y);

int comidinha=1;

typedef struct{
	NODO *INICIO;
	NODO *FIM;	
}DESCRITOR;

typedef DESCRITOR * FILA_ENC;

void mudar_direcao(FILA_ENC f, int dir);
void cria_fila(FILA_ENC *f);
int eh_vazia(FILA_ENC f);
void ins(FILA_ENC f, int val);
int consulta(FILA_ENC f);
void ret(FILA_ENC f);
int tam(FILA_ENC f);

//int main(){/////////////////////////////////////////////////////////////
//FILA_ENC f1;
//
//cria_fila(&f1);
//NODO **aux;
//aux=&f1->INICIO;
//
//ins(f1,9);
//ins(f1,1);
// ins(f1,3);
//ins(f1,5);
//ins(f1,10);
//
//int i,j=tam(f1);
//for (i=0; i<j; i++){
//	printf ("%d,", (*aux)->direcao);
//	(*aux)=(*aux)->next;
//}
//
//	return 0;
//}//////////////////////////////////////////////////////////////////////

void cria_fila(FILA_ENC *f){
	*f = (DESCRITOR *) malloc (sizeof (DESCRITOR));
	if (!*f){printf ("Memoria nao alocada, encerrando!"); exit(0);	}
	
	(*f)->INICIO=(*f)->FIM=NULL;
}

int eh_vazia(FILA_ENC f){
	return (f->INICIO==NULL);
}

void ins(FILA_ENC f, int val){
	NODO *novo=(NODO*) malloc (sizeof(NODO));
	if (!novo){printf ("Memoria nao alocada, encerrando..."); exit(1);	}
	novo->next=NULL;
	novo->ant=NULL;
	
	if (!f->INICIO){//se fila vazia
		novo->direcao=val;
		novo->pos[1]=0; //posição inicial x
		novo->pos[2]=0; //posição inicial y
		f->INICIO=f->FIM=novo;
	}else {
		novo->pos[1]=f->FIM->pos[1]; // O NOVO ELEMENTO VAI APARECER NA POSIÇÃO DO ANTIGO ÚLTIMO 
		novo->pos[2]=f->FIM->pos[2]; // O NOVO ELEMENTO VAI APARECER NA POSIÇÃO DO ANTIGO ÚLTIMO
		novo->ant=f->FIM;
		f->FIM->next=novo;
		f->FIM=novo;
		if(comidinha==1){
			gotoxy(17,0);
			printf ("nhame nhame nhame       ");
			comidinha++;
		}else if(comidinha==2) {
			gotoxy(17,0);
			printf ("q denicia                     ");
			comidinha++;
		}else {
			gotoxy(17,0);
			printf ("comidas me deixam feliz");
			comidinha=1;
		}
		Beep(1000,100);
	}
}

int consulta(FILA_ENC f){
	if(eh_vazia(f)){
		printf ("\nfila vazia, n foi possivel consultar.");
		return 0;
	}
	return (f->INICIO->direcao);
}

void ret(FILA_ENC f){
	NODO *aux=f->INICIO;
	if (eh_vazia(f)){
		printf ("\nretirada invalida, lista vazia");
	}
	
	f->INICIO=f->INICIO->next;
	free(aux);
	if (eh_vazia(f)){
		f->FIM=NULL;
	}
}


int tam(FILA_ENC f){
	NODO *aux=f->INICIO;
	int i=0;
	while (aux){
		aux=aux->next;
		i++;
	}
	return i;
}

void mudar_direcao(FILA_ENC f, int dir){
	f->INICIO->direcao=dir;
}

void gotoxy(int x, int y)
{
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){y,x});
}  
