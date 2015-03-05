#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int main(int argc, const char * argv[]) {
    int n=1, i, j;
    
    scanf("%d", &n);
    
    int tabela[n][n];
    int vagao[n];
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            tabela[i][j] = 0;
        }
    }
    
    for(i=0;i<n;i++){
        scanf("%d", &vagao[i]);
    }

    int percorrido = 0;
    int percorrer =n;

    do{
        for(i=0;i<percorrer;i++){
            for(j=i+percorrido;j<n;j++){
                tabela[i][j] = MAX(vagao[i]+MIN(tabela[i+2][j],tabela[i+1][j-1]),
                                   vagao[j]+MIN(tabela[i+1][j-1],tabela[i][j-2]));
            }
        }
        percorrido++;
        percorrer--;
    }while(percorrido<n);
    
    
    printf("%d\n", tabela[0][n-1]);
    
    return 0;
}
