#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXIMO 5000
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int carruagem[MAXIMO];

int escolha(int principio, int fim){
    int valor1, valor2, valormax;
    if(fim == principio+1){
        return MAX(carruagem[principio],carruagem[fim]);
    }
    if(fim==principio){
        return carruagem[principio];
    }
    
    valor1=carruagem[principio]+MIN(escolha(principio+2,fim),escolha(principio+1,fim-1));
    valor2=carruagem[fim]+MIN(escolha(principio+1,fim-1),escolha(principio,fim-2));
    
    valormax = MAX(valor1,valor2);
    
    return valormax;
}

int main() {
    int n,i;
    int valorladrao;
    clock_t start, end;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &carruagem[i]);
    }
    //start = time(NULL);
    valorladrao=escolha(0,n-1);
    //end = time(NULL);
    
    printf("%dn", valorladrao);
    return 0;
}