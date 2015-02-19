#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 5000

int main() {
    int valor=0, n,i,contador;
    int carruagem[MAXIMO];
    
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &carruagem[i]);
    }
    i=0;
    contador = 0;
    while(i<n){
        if(carruagem[i] >= carruagem[n-1]){
            if(contador % 2 == 0)
                valor += carruagem[i];
            i++;
        }else{
            if(contador % 2 == 0)
                valor += carruagem[n-1];
            n--;
        }
        contador++;
    }
    
    printf("%d\n", valor);
    return 0;
}
