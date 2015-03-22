#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct no *No;
typedef struct no{
    
    char *matricula;
    char *estado;
    int passagens;
    int peso;
    No left;
    No right;
    
} Nos;

No arvore = NULL;

int CalculaPeso(No actual)
{
    if( actual == NULL )
        return -1;
    else
        return actual->peso;
}

No single_rotate_with_left( No k2 )
{
    No k1 = NULL;
    
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    
    k2->peso = MAX( CalculaPeso( k2->left ), CalculaPeso( k2->right ) ) + 1;
    k1->peso = MAX( CalculaPeso( k1->left ), k2->peso ) + 1;
    return k1;
}

No single_rotate_with_right( No k1 )
{
    No k2;
    
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    
    k1->peso = MAX( CalculaPeso( k1->left ), CalculaPeso( k1->right ) ) + 1;
    k2->peso = MAX( CalculaPeso( k2->right ), k1->peso ) + 1;
    
    return k2;
}

No double_rotate_with_left( No k3 )
{
    /* Rotate between k1 and k2 */
    k3->left = single_rotate_with_right( k3->left );
    
    /* Rotate between K3 and k2 */
    return single_rotate_with_left( k3 );
}

No double_rotate_with_right( No k1 )
{
    /* rotate between K3 and k2 */
    k1->right = single_rotate_with_left( k1->right );
    
    /* rotate between k1 and k2 */
    return single_rotate_with_right( k1 );
}

No inserirNaArvore(char *m, char *e, No actual){
    
    if(actual == NULL){
        actual = (No) malloc(sizeof(Nos));
        actual->matricula = malloc(sizeof(char *));
        actual->estado = malloc(sizeof(char *));
        strcpy(actual->matricula, m);
        strcpy(actual->estado, e);
        actual->passagens = 1;
        actual->peso = 0;
        actual->left = NULL;
        actual->right = NULL;
    }else if(strcmp(actual->matricula, m) > 0 ){
        actual->left = inserirNaArvore(m, e, actual->left);
        if( CalculaPeso( actual->left ) - CalculaPeso( actual->right ) == 2 ){
            if(strcmp(actual->left->matricula, m) > 0){
                actual = single_rotate_with_left( actual );
            }
            else{
                actual = double_rotate_with_left( actual );
            }
        }
    }else{
        actual->right = inserirNaArvore(m, e, actual->right);
        if( CalculaPeso( actual->right ) - CalculaPeso( actual->left ) == 2 ){
            if( strcmp(actual->right->matricula, m) < 0){
                actual = single_rotate_with_right( actual );
            }
            else{
                actual = double_rotate_with_right( actual );
            }
        }
    }
    actual->peso = MAX( CalculaPeso( actual->left ), CalculaPeso( actual->right ) ) + 1;
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
