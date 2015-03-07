#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no *No;
typedef struct no{
  
    char *matricula;
    char *estado;
    int passagens;
    No left;
    No right;

} Nos;

No arvore = NULL;

No inserirNaArvore(char *m, char *e, No actual){
    
    if(actual == NULL){
        actual = (No) malloc(sizeof(Nos));
        actual->matricula = malloc(sizeof(char *));
        actual->estado = malloc(sizeof(char *));
        strcpy(actual->matricula, m);
        strcpy(actual->estado, e);
        actual->passagens = 1;
        actual->left = NULL;
        actual->right = NULL;
    }else if(strcmp(actual->matricula, m) > 0 ){
        actual->left = inserirNaArvore(m, e, actual->left);
    }else{
        actual->right = inserirNaArvore(m, e, actual->right);
    }
    return actual;
}

int localiza(char *m, char *e, No actual){
    
    if(actual==NULL){
        return 1;
    }else if(strcmp(actual->matricula, m) == 0 ){
        actual->passagens=actual->passagens+1;
        strcpy(actual->estado,e);
        return 0;
    }else if(strcmp(actual->matricula, m) > 0 ){
        return localiza(m, e, actual->left);
    }else{
        return localiza(m, e, actual->right);
    }
    
}

void unFlag(char *m,No actual){
    if(actual!=NULL){
        if(strcmp(actual->matricula, m) == 0 ){
            strcpy(actual->estado,"R");
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
            printf("%s %d %s\n", actual->matricula,actual->passagens,actual->estado);
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
        printf("matricula %s Estado %s Passagens %d\n", actual->matricula,
                                                        actual->estado,
                                                        actual->passagens);
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
                arvore=inserirNaArvore(matricula, estadi, arvore);
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
