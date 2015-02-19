#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 5000

int carruagem[MAXIMO];
int valorladrao=0;

void escolha(int principio, int fim, int valor, int contador){
    
    fim -= 1;
    
    if(principio < fim){
        if(contador % 2 == 0){
            
            if(carruagem[principio] > carruagem[fim])
                if(carruagem[principio+1] < carruagem[principio])
                    escolha(principio+1,fim,valor+carruagem[principio],contador+1);
                else
                    escolha(principio,fim,valor+carruagem[fim],contador+1);
            else if (carruagem[principio] < carruagem[fim])
                if(carruagem[fim-1] < carruagem[fim])
                    escolha(principio,fim,valor+carruagem[fim],contador+1);
                else
                    escolha(principio+1,fim,valor+carruagem[principio],contador+1);
            else
                if(carruagem[principio+1] > carruagem[fim-1]){
                    escolha(principio,fim,valor+carruagem[fim],contador+1);
                }else
                    escolha(principio+1,fim,valor+carruagem[principio],contador+1);
            
        }else{
            if(carruagem[principio] > carruagem[fim])
                if(carruagem[principio+1] < carruagem[principio])
                    escolha(principio+1,fim,valor,contador+1);
                else
                    escolha(principio,fim,valor,contador+1);
                else if (carruagem[principio] < carruagem[fim])
                    if(carruagem[fim-1] < carruagem[fim])
                        escolha(principio,fim,valor,contador+1);
                    else
                        escolha(principio+1,fim,valor,contador+1);
                    else
                        if(carruagem[principio+1] > carruagem[fim-1]){
                            escolha(principio,fim,valor,contador+1);
                        }else
                            escolha(principio+1,fim,valor,contador+1);
        }
    }else{
        if(valorladrao<valor)
            valorladrao=valor;
    }
}

int main() {
    int n,i;
    
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &carruagem[i]);
    }
    
    escolha(0,n,0,0);
    
    printf("%d\n", valorladrao);
    return 0;
}