#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char *matricula;
    char *estado;
    int passagens;
    char color;
    
    struct node *left, *right, *parent;
};



void LeftRotate(struct node **root,struct node *x)
{

    struct node *y = NULL;
    y = x->right;
    x->right = y->left;
    if (x->right != NULL)
        x->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        (*root) = y;
    
    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;

    y->left = x;
    x->parent = y;
}



void rightRotate(struct node **root,struct node *y)
{
    struct node *x = NULL;
        x = y->left;
    
    if(x != NULL){
        y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    
    x->parent =y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
        }
}

void insertFixUp(struct node **root,struct node *z)
{
    while (z != NULL && z != *root && z->parent->color == 'R')
    {
        struct node *y = NULL;
        
        
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;
        
        
        if (y != NULL && y->color == 'R')
        {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }
        
        else
        {

            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                //rightRotate(root,z->parent->parent);
            }else
            
            if (z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                //LeftRotate(root,z->parent);
                //rightRotate(root,z->parent->parent);
            }else
            
            if (z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                //LeftRotate(root,z->parent->parent);
            }else
            
            if (z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                //rightRotate(root,z->parent);
                //LeftRotate(root,z->parent->parent);
            }

        }
    }
    (*root)->color = 'B';
}

void insert(char *m, char *e, struct node **root)
{

    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->matricula = malloc(sizeof(char *));
    z->estado = malloc(sizeof(char *));
    strcpy(z->matricula, m);
    strcpy(z->estado, e);
    z->passagens = 1;
    z->left = z->right = z->parent = NULL;
    
    if (*root == NULL)
    {
        z->color = 'B';
        (*root) = z;
    }
    else
    {
        struct node *y = NULL;
        struct node *x = (*root);
        
        while (x != NULL)
        {
            y = x;
            if (strcmp(z->matricula, x->matricula) < 0)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (strcmp(z->matricula, y->matricula) > 0)
            y->right = z;
        else
            y->left = z;
        z->color = 'R';
        
        insertFixUp(root,z);
    }
}


int localiza(char *m, char *e, struct node *actual){
    
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

void unFlag(char *m,struct node *actual){
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

void status(char *m,struct node *actual){
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


void imprimirArvore(struct node *actual){
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
    
    struct node *arvore = NULL;
    
    char *string = malloc(sizeof(5));
    char *matricula = malloc(sizeof(6));
    char *estadi = malloc(sizeof(1));
    while(scanf("%s", string) != EOF){
        if(strcmp(string, "PASS")==0){
            scanf("%s", matricula);
            scanf("%s", estadi);
            if(localiza(matricula, estadi, arvore)){
                insert(matricula, estadi, &arvore);
            }
        }
        if(strcmp(string, "UNFLAG")==0){
            scanf("%s", matricula);
            unFlag(matricula, arvore);
        }
        if(strcmp(string, "STATUS")==0){
            scanf("%s", matricula);
            status(matricula, arvore);
        }
        
    }
    
    
    return 0;
}
