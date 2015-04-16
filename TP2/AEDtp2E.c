#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

int travesia=0,rotacoes=0;

typedef struct no *No;
typedef struct no{
    
    char *matricula;
    char *estado;
    int passagens;
    int peso;
    No pai;
    No left;
    No right;
    
} Nos;

No arvore = NULL;


No single_rotate_with_left( No node )
{
    No auxNode = node->right;
    auxNode->pai = node->pai;
    
    node->right = auxNode->left;
    
    if(node->right != NULL) {
        node->right->pai = node;
    }
    
    auxNode->left = node;
    node->pai = auxNode;
    
    if(auxNode->pai != NULL) {
        if(auxNode->pai->right == node) {
            auxNode->pai->right = auxNode;
        } else if(auxNode->pai->left == node) {
            auxNode->pai->left = auxNode;
        }
    } else {
        arvore = auxNode;
    }
    
    return auxNode;
}

No single_rotate_with_right( No node )
{

    No auxNode = node->left;
    auxNode->pai = node->pai;
    
    node->left = auxNode->right;
    
    if(node->left != NULL) {
        node->left->pai = node;
    }
    
    auxNode->right = node;
    node->pai = auxNode;
    
    
    if(auxNode->pai != NULL) {
        if(auxNode->pai->right == node) {
            auxNode->pai->right = auxNode;
        } else if(auxNode->pai->left == node) {
            auxNode->pai->left = auxNode;
        }
    } else {
        arvore = auxNode;
    }
    
    return auxNode;
    
    
}

No getParent(No node) {
    if(node == NULL) {
        return NULL;
    } else {
        return node->pai;
    }
}

No getRight(No node) {
    if(node != NULL) {
        return node->right;
    } else {
        return NULL;
    }
}

void recuriveBalance(No node){
    if(node->pai != NULL && node->peso > node->pai->peso){
        if(getRight(getParent(node)) == node){
            single_rotate_with_left(node->pai);
        }else{
            single_rotate_with_right(node->pai);
        }
        recuriveBalance(node);
    }
}

No inserirNaArvore(char *m, char *e, No actual, No anterior){
    
    if(actual == NULL){
        actual = (No) malloc(sizeof(Nos));
        actual->matricula = malloc(sizeof(char *));
        actual->estado = malloc(sizeof(char *));
        strcpy(actual->matricula, m);
        strcpy(actual->estado, e);
        actual->passagens = 1;
        actual->peso = 0;
        actual->pai = anterior;
        actual->left = NULL;
        actual->right = NULL;
    }else if(strcmp(actual->matricula, m) > 0 ){
        travesia++;
        actual->left = inserirNaArvore(m, e, actual->left, actual);
    }else{
        travesia++;
        actual->right = inserirNaArvore(m, e, actual->right, actual);
    }
    return actual;
}

int localiza(char *m, char *e, No actual){
    
    if(actual==NULL){
        return 1;
    }else if(strcmp(actual->matricula, m) == 0 ){
        actual->passagens=actual->passagens+1;
        strcpy(actual->estado,e);
        actual->peso++;
        recuriveBalance(actual);
        return 0;
    }else if(strcmp(actual->matricula, m) > 0 ){
        travesia++;
        return localiza(m, e, actual->left);
    }else{
        travesia++;
        return localiza(m, e, actual->right);
    }
    
}

void unFlag(char *m,No actual){
    if(actual!=NULL){
        if(strcmp(actual->matricula, m) == 0 ){
            actual->peso++;
            strcpy(actual->estado,"R");
            recuriveBalance(actual);
        }else if(strcmp(actual->matricula, m) > 0 ){
            unFlag(m, actual->left);
        }else{
            unFlag(m, actual->right);
        }
    }
}

void status(char *m,No actual){
    if(actual!=NULL){
        if(strcmp(actual->matricula, m) == 0 ){
            actual->peso++;
            printf("%s %d %s\n", actual->matricula,actual->passagens,actual->estado);
            recuriveBalance(actual);
        }else if(strcmp(actual->matricula, m) > 0 ){
            status(m, actual->left);
        }else{
            status(m, actual->right);
        }
    }else{
        printf("%s NO RECORD\n", m);
    }
}


void imprimirArvore(No actual){
    if(actual != NULL)
    {
        imprimirArvore(actual->left);
        printf("matricula %s Estado %s usado: %d\n", actual->matricula,
               actual->estado,
               actual->peso);
        imprimirArvore(actual->right);
    }
}

int main() {
    char *string = malloc(sizeof(5));
    char *matricula = malloc(sizeof(6));
    char *estadi = malloc(sizeof(1));
    while(scanf("%s", string) != EOF){
        if(strcmp(string, "PASS")==0){
            scanf("%s", matricula);
            scanf("%s", estadi);
            if(localiza(matricula, estadi,arvore)){
                arvore=inserirNaArvore(matricula, estadi, arvore,NULL);
            }
        }
        if(strcmp(string, "UNFLAG")==0){
            scanf("%s", matricula);
            unFlag(matricula,arvore);
        }
        if(strcmp(string, "STATUS")==0){
            scanf("%s", matricula);
            status(matricula, arvore);
        }
        
    }
    
    
    return 0;
}
