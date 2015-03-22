#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no *No;
typedef struct no{
    
    char *matricula;
    char *estado;
    int passagens;
    int cor;
    No pai;
    No left;
    No right;
    
} Nos;

void LeftRotate(No *root,No x)
{
    No y = x->right;
    
    x->right = y->left;
    
    if (x->right != NULL)
        x->right->pai = x;
    
    y->pai = x->pai;
    
    if (x->pai == NULL)
        (*root) = y;
    
    else if (x == x->pai->left)
        x->pai->left = y;
    else    x->pai->right = y;
    

    y->left = x;
    x->pai = y;
}


void rightRotate(No *root,No y)
{
    No x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->pai = y;
    x->pai =y->pai;
    if (x->pai == NULL)
        (*root) = x;
    else if (y == y->pai->left)
        y->pai->left = x;
    else y->pai->right = x;
    x->right = y;
    y->pai = x;
}

void insertFixUp(No *root,No z)
{
    while (z != *root && z->pai->cor == 1)
    {
        No y;
        
        if(z->pai->pai != NULL){
            if (z->pai == z->pai->pai->left)
                y = z->pai->pai->right;
            else
                y = z->pai->pai->left;
        }else{
            break;
        }
        
        if(y == NULL){
            y = (No) malloc(sizeof(Nos));
            y->cor = 0;
        }
        
        if (y->cor == 1)
        {
            y->cor = 0;
            z->pai->cor = 0;
            z->pai->pai->cor = 1;
            z = z->pai->pai;
        }else{
            if (z->pai == z->pai->pai->left &&
                z == z->pai->left)
            {
                int ch = z->pai->cor ;
                z->pai->cor = z->pai->pai->cor;
                z->pai->pai->cor = ch;
                rightRotate(root,z->pai->pai);
                break;
            }

            if (z->pai == z->pai->pai->left &&
                z == z->pai->right)
            {
                int ch = z->cor ;
                z->cor = z->pai->pai->cor;
                z->pai->pai->cor = ch;
                LeftRotate(root,z->pai);
                rightRotate(root,z->pai->pai);
                break;
            }
            

            if (z->pai == z->pai->pai->right &&
                z == z->pai->right)
            {
                int ch = z->pai->cor ;
                z->pai->cor = z->pai->pai->cor;
                z->pai->pai->cor = ch;
                LeftRotate(root,z->pai->pai);
                break;
            }
            

            if (z->pai == z->pai->pai->right &&
                z == z->pai->left)
            {
                int ch = z->cor ;
                z->cor = z->pai->pai->cor;
                z->pai->pai->cor = ch;
                rightRotate(root,z->pai);
                LeftRotate(root,z->pai->pai);
                break;
            }
        }
    }
    (*root)->cor = 0;
}

void inserirNaArvore(char *m, char *e, No *root){
    
    No actual = (No) malloc(sizeof(Nos));
    actual->matricula = malloc(sizeof(char *));
    actual->estado = malloc(sizeof(char *));
    strcpy(actual->matricula, m);
    strcpy(actual->estado, e);
    actual->passagens = 1;
    actual->cor = 1;
    actual->pai = NULL;
    actual->left = NULL;
    actual->right = NULL;
    
    if(*root == NULL){
        (*root)=actual;
        
    }else{
        No y = NULL;
        No x = (*root);
        
        while (x != NULL)
        {
            y = x;
            if (strcmp(actual->matricula ,x->matricula) < 0)
                x = x->left;
            else
                x = x->right;
        }
        actual->pai= y;
        if (strcmp(actual->matricula,  y->matricula) > 0)
            y->right = actual;
        else
            y->left = actual;
        actual->cor = 1;
        

        insertFixUp(root,actual);
        
        
    }
    
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
    
    No arvore = NULL;
    
    char *string = malloc(sizeof(5));
    char *matricula = malloc(sizeof(6));
    char *estadi = malloc(sizeof(1));
    while(scanf("%s", string) != EOF){
        if(strcmp(string, "PASS")==0){
            scanf("%s", matricula);
            scanf("%s", estadi);
            if(localiza(matricula, estadi,arvore)){
                inserirNaArvore(matricula, estadi, &arvore);
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
