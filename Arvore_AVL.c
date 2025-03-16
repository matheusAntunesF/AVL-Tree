#include "Arvore_AVL.h"
#include<stdio.h>
#include<stdlib.h>

void imprime_rec(Arvore arv) {
  if (arv == NULL) {
    printf(".");
    return;
  }
  printf("[%d:e=", arv->valor);
  imprime_rec(arv->esq);
  printf(",d=");
  imprime_rec(arv->dir);
  printf("]");
}

void imprime(Arvore arv) {
  imprime_rec(arv);
  printf("\n");
}

No* novoNo(int x){
	No* novo = (No*) malloc(sizeof(No));
	if(novo){
		novo->valor = x;
		novo->dir = novo->esq = NULL;
		novo->altura = 0;
		return novo;
	}
	return NULL;
}

int maior(int esq, int dir){
	return (esq > dir)? esq: dir;
}

int altura(Arvore arv){
	if(arv == NULL) 
		return -1;
	else
		return arv->altura;
}

int fator_balanc(Arvore arv){
	if(arv)
		return (altura(arv->esq) - altura(arv->dir));
	return 0;
}

No* rodaDir(No* raiz){
	Arvore fesq = raiz->esq;
	Arvore arvmeio = fesq->dir;

	fesq->dir = raiz;
	raiz->esq = arvmeio;

	raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
	fesq->altura = maior(altura(fesq->esq), altura(fesq->dir)) + 1;
	
	return fesq;
}

No* rodaEsq(No* raiz){
	Arvore fdir = raiz->dir;
	Arvore arvmeio = fdir->esq;

	fdir->esq = raiz;
	raiz->dir = arvmeio;
	
	raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
	fdir->altura = maior(altura(fdir->esq), altura(fdir->dir)) + 1;
	
	return fdir;
}

No* rodaDirEsq(No* raiz){
	raiz->dir = rodaDir(raiz->dir);
	return rodaEsq(raiz);
}

No* rodaEsqDir(No* raiz){
	raiz->esq = rodaEsq(raiz->esq);
	return rodaDir(raiz);
}
No* balanceia(No* raiz){
	int fb = fator_balanc(raiz);

	if(fb < -1 && fator_balanc(raiz->dir) <= 0){
		raiz = rodaEsq(raiz);
	} 
	else if(fb > 1 && fator_balanc(raiz->esq) >= 0){
		raiz = rodaDir(raiz);
	}
	else if(fb > 1 && fator_balanc(raiz->esq) < 0){
		raiz = rodaEsqDir(raiz);
	}
	else if(fb < -1 && fator_balanc(raiz->dir) > 0){
		raiz = rodaDirEsq(raiz);
	}
	return raiz;
}

No* insereRec(No* raiz, int x){
	if(raiz == NULL){
		return novoNo(x);
	} else{
		if(x < raiz->valor)
			raiz->esq = insereRec(raiz->esq, x);
		if(x > raiz->valor)
			raiz->dir = insereRec(raiz->dir, x);
	}
	raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
	raiz = balanceia(raiz);

	return raiz;
}

bool busca(Arvore arv, int x){
	if(arv == NULL) return false;
	if(arv->valor == x) return true;
	if(x > arv->valor) return busca(arv->dir, x);
	return busca(arv->esq, x);
}

bool insere(Arvore* ap_arv, int x){
	if(busca(*ap_arv, x)) return false;
	(*ap_arv) = insereRec(*ap_arv, x);
	if((*ap_arv) == NULL) return false;

	return true;
}
