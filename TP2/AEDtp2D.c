#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct no *No;
typedef struct no{
    
    char *matricula;
    char *estado;
    int passagens;
    int size;
    No left;
    No right;
    
} Nos;

No arvore = NULL;



int localiza(char *m, char *e, No actual){
    
    if(actual==NULL){
        return 1;
    }else if(strcmp(actual->matricula, m) == 0 ){
        actual->passagens=actual->passagens+1;
        strcpy(actual->estado,e);
        return 0;
    }else if(strcmp(actual->matricula, m) < 0 ){
        return localiza(m, e, actual->left);
    }else{
        return localiza(m, e, actual->right);
    }
    
}

No unFlag(char *m,No actual){
    if(actual!=NULL){
        if(strcmp(actual->matricula, m) == 0 ){
            strcpy(actual->estado,"R");
            return actual;
        }else if(strcmp(actual->matricula, m) < 0 ){
            return unFlag(m, actual->left);
        }else{
            return unFlag(m, actual->right);
        }
    }
    
    return NULL;
}

void status(char *m,No actual){
    if(actual!=NULL){
        if(strcmp(actual->matricula, m) == 0 ){
            printf("%s %d %s\n", actual->matricula,actual->passagens,actual->estado);
        }else if(strcmp(actual->matricula, m) < 0 ){
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
        printf("matricula %s Estado %s Passagens %d\n", actual->matricula,
               actual->estado,
               actual->passagens);
        imprimirArvore(actual->right);
    }
}

int calculaTamanho(No node)
{
    int tamEsq=0, tamDir=0, tamanho;
    if (node->left!=NULL) {
        tamEsq = calculaTamanho(node->left);
    }
    if (node->right!=NULL) {
        tamDir = calculaTamanho(node->right);
    }
    tamanho = tamEsq + tamDir + 1;
    node->size = tamanho;
    return tamanho;
}

void calculaTam(No raiz){
    raiz->size = calculaTamanho(raiz);
}

No insereN(No node, No aux)
{
    if(node==NULL){
        node=aux;
        return node;
    }
    else{
        if(strcmp(node->matricula, aux->matricula) < 0){
            node->left=insereN(node->left, aux);
        }
        else{
            node->right=insereN(node->right, aux);
        }
    }
    return node;
}

No insereRaiz(No novo, No node){
    if(node!=NULL){
        if(strcmp(novo->matricula,node->matricula) < 0){
            novo=insereN(novo,node);
        }
        else{
            novo=insereN(novo,node);
        }
        return novo;
    }
    return novo;
}

No insere(No novo, No anterior)
{
    if(anterior==NULL){
        anterior=novo;
        return anterior;
    }
    else{
        srand(time(NULL));
        int r = rand() % 100 + 1;
        double random = r/100.0;
        double tam=anterior->size;
        double prob=(1/(tam+1));
        if(random>=prob){
            novo = insereRaiz(novo, anterior);
            return novo;
        }
        else if(strcmp(novo->matricula,anterior->matricula) < 0){
            anterior->left=insere(novo,anterior->left);
        }
        else{
            anterior->right=insere(novo,anterior->right);
        }
        return anterior;
    }
}

No insertNo(char *m, char *e, No actual)
{
    No novoNo = NULL;
    novoNo = (No) malloc(sizeof(Nos));
    novoNo->matricula = malloc(sizeof(char *));
    novoNo->estado = malloc(sizeof(char *));
    strcpy(novoNo->matricula, m);
    strcpy(novoNo->estado, e);
    novoNo->passagens = 1;
    novoNo->left = NULL;
    novoNo->right = NULL;
    
    if(actual!=NULL)
    {
        calculaTam(actual);
    }
    actual = insere(novoNo, actual);
    return actual;
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
                arvore = insertNo(matricula, estadi, arvore);
            }
        }
        if(strcmp(string, "UNFLAG")==0){
            scanf("%s", matricula);
            arvore = unFlag(matricula,arvore);
        }
        if(strcmp(string, "STATUS")==0){
            scanf("%s", matricula);
            status(matricula, arvore);
        }
        
    }
    
    return 0;
}
