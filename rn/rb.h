#ifndef RB_H
#define RB_H

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct no_rb{
    int dado;
    enum cor cor;
    struct no_rb *pai, *esq, *dir;
}no_rb;

typedef no_rb *arvore;

int altura(arvore a);

// FUNÇÕES BÁSICAS

void inicializar(arvore *raiz);
void adicionar(arvore *raiz, int valor);
void remover(arvore *raiz, int valor);

void imprimir_elemento(arvore raiz);
void imprimir(arvore raiz);

// FUNÇÕES AUXILIARES

enum cor cor(arvore elemento);
int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
int eh_filho_direito(arvore elemento);
arvore irmao(arvore elemento);
arvore tio(arvore elemento);
int maior_elemento(arvore raiz);
void retira_duplo_preto(arvore *raiz, arvore elemento);

//AJUSTES
void ajustar(arvore *raiz, arvore elemento);
void rotacao_simples_direita(arvore *raiz, arvore pivo);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);
void rotacao_dupla_direita(arvore *raiz, arvore pivo);
void rotacao_dupla_esquerda(arvore *raiz, arvore pivo);
void reajustar(arvore *raiz, arvore elemento);

#endif
