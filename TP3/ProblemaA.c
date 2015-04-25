#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct palavras{
    char *valor;
    int contagem;
    struct palavras *next;
} Palavras;

Palavras *lista = NULL;
int maior=1;

void inserir(Palavras *token, Palavras *actual, Palavras *anterior){
    if(strcasecmp(token->valor, actual->valor)<0){
        if(anterior != NULL){
            token->next = actual;
            anterior->next = token;
        }else{
            token->next = actual;
            lista = token;
        }
    }else if(strcasecmp(token->valor, (actual->valor)) == 0){
        actual->contagem = actual->contagem + 1;
        if(maior<actual->contagem){
            maior=actual->contagem;
        }
    }else{
        if(actual->next != NULL){
            inserir(token, actual->next, actual);
        }else{
            actual->next = token;
        }
    }
}

void printstrings(Palavras *actual, int tamanho){
    if(actual != NULL){
        if(tamanho==actual->contagem)
            printf("%s %d\n", actual->valor, actual->contagem);
        printstrings(actual->next, tamanho);
    }
}

int main(){

    int i, numerolinhas, n;
    char buff[254];
    char *retirar=malloc(sizeof(char));
    char *token;
    scanf("%d", &n);
    Palavras stop[n];
    for(i=0;i<n;i++){
        scanf("%s", retirar);
        stop[i].valor = malloc(sizeof(char));
        strcpy(stop[i].valor, retirar);
    }

    scanf("%d\n", &numerolinhas);
        for(i=0;i<numerolinhas;i++){
            int j;
            fgets(buff, sizeof(buff), stdin);
            buff[strcspn(buff, "\n")] = 0;
            for(j=0;j<254;j++)
                buff[j] = tolower(buff[j]);
            token = strtok(buff, " .,;:?!-_@#$%&*+()\t");
            while(token != NULL){
                int posso=0;
                for(j=0;j<n;j++){
                    if(strcasecmp(token, stop[j].valor) == 0){
                        posso=1;
                        break;
                    }
                }
                Palavras *novo = (Palavras*)malloc(sizeof(Palavras));
                novo->valor = (char *)malloc(sizeof(char));
                strcpy(novo->valor, token);
                novo->contagem = 1;
                novo->next = NULL;
                if(posso==0){
                    if(lista == NULL){
                        lista = novo;
                    }else{
                        inserir(novo, lista, NULL);
                    }
                }
                token = strtok(NULL, " .,;:?!-_@#$%&*+()\t");
            }

        }

    while(maior != 0){
        printstrings(lista, maior);
        maior--;

    }


    return 0;
}
