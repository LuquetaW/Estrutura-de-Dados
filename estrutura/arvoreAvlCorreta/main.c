#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct no {
    int dado, bal;
    struct no *esq;
    struct no *dir;
};

struct no *raiz_avl = NULL;

struct no *cria_no(int valor) {
    struct no *aux = malloc(sizeof(struct no));
    aux->dado = valor;
    aux->dir = NULL;
    aux->esq = NULL;
    aux->bal = 0;
    return aux;
}

void esquerda(struct no *p){
    struct no *q, *hold;
    q = p->dir;
    hold = q->esq;
    q->esq = p;
    p->dir = hold;

    // Agora q � o novo topo da sub�rvore, ent�o devemos atualizar o ponteiro pai fora daqui
    // Esse ajuste � feito na insere_bal (como voc� j� faz depois com: pnovo->dir = p)
}

void direita(struct no *p){
    struct no *q, *hold;
    q = p->esq;
    hold = q->dir;
    q->dir = p;
    p->esq = hold;

    // Mesmo caso: quem chama essa fun��o precisa atualizar o ponteiro do pai
}

void insere_bal(int chave){
    struct no *pp = NULL, *p = raiz_avl, *pnovo = NULL, *anovo = raiz_avl, *q, *filho;
    int imbal;

    if(p == NULL){
        raiz_avl = cria_no(chave);
        return;
    }

    while (p != NULL){
        if(chave < p->dado){
            q = p->esq;
        } else {
            q = p->dir;
        }

        if(q != NULL){
            if(q->bal != 0){
                pnovo = p;
                anovo = q;
            }
        }

        pp = p;
        p = q;
    }

    q = cria_no(chave);

    if(chave < pp->dado){
        pp->esq = q;
    } else {
        pp->dir = q;
    }

    if(chave < anovo->dado){
        filho = anovo->esq;
    } else {
        filho = anovo->dir;
    }

    p = filho;

    while(p != q){
        if(chave < p->dado){
            p->bal = 1;
            p = p->esq;
        } else {
            p->bal = -1;
            p = p->dir;
        }
    }

    if(chave < anovo->dado){
        imbal = 1;
    } else {
        imbal = -1;
    }

    if(anovo->bal == 0){
        anovo->bal = imbal;
        return;
    }

    if(anovo->bal != imbal){
        anovo->bal = 0;
        return;
    }

    if(filho->bal == imbal){
        p = filho;
        if(imbal == 1){
            printf("Desbalanceamento simples a direita\n");
            direita(anovo);
        } else {
            printf("Desbalanceamento simples a esquerda\n");
            esquerda(anovo);
        }
        anovo->bal = 0;
        filho->bal = 0;
    } else {
        if(imbal == 1){
            p = filho->dir;
            esquerda(filho);
            anovo->esq = p;
            printf("Desbalanceamento duplo a direita\n");
            direita(anovo);
        } else {
            p = filho->esq;
            direita(filho);
            anovo->dir = p;
            printf("Desbalanceamento duplo a esquerda\n");
            esquerda(anovo);
        }

        if(p->bal == 0){
            anovo->bal = 0;
            filho->bal = 0;
        } else {
            if(p->bal == imbal){
                anovo->bal = -imbal;
                filho->bal = 0;
            } else {
                anovo->bal = 0;
                filho->bal = imbal;
            }
        }
        p->bal = 0;
    }

    if(pnovo == NULL){
        raiz_avl = p;
    } else {
        if(anovo == pnovo->dir){
            pnovo->dir = p;
        } else {
            pnovo->esq = p;
        }
    }

    return;
}


// Fun��o para imprimir in-order (para testes)
void in_order(struct no *raiz) {
    if (raiz != NULL) {
        in_order(raiz->esq);
        printf("%d ", raiz->dado);
        in_order(raiz->dir);
    }
}

int main() {
    //set_locale(LC_ALL, "Portuguese");

    insere_bal(10);
    insere_bal(20);
    insere_bal(30);
    insere_bal(40);
    insere_bal(50);
    insere_bal(60);
    insere_bal(9);
    insere_bal(8);
    insere_bal(70);
    insere_bal(80);
    insere_bal(7);

    printf("In-order: ");
    in_order(raiz_avl);
    printf("\n");

    return 0;
}
