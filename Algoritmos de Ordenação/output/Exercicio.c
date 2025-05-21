#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define N 19999

int A[N], th, scratch[N];

void gera_vetor(){
    int i;
    srand(10);
    for(i = 0; i < N; i++){
        A[i] = rand() % (N * 10);
    }
}

void selection_sort(int lista[], int n){
    int i, j, min, pivo;
    for(i = 0; i < n - 1; i++){
        pivo = i;
        for(j = i + 1; j < n; j++){
            if(lista[pivo] > lista[j]){
                pivo = j;
            }
        }
        if(pivo != i){
            int aux = lista[i];
            lista[i] = lista[pivo];
            lista[pivo] = aux;
        }
    }
}

void inserction_sort(int lista[], int n){
    int i, j, pivo;
    for(i = 1; i < n; i++){
        pivo = lista[i];
        j = i - 1;
        while(j >= 0 && pivo < lista[j]){
            lista[j+1] = lista[j];
            j--;
        }
        lista[j+1] = pivo;
    }
}

void bubble_sort3(int lista[], int n){
    int i, j, aux;
    int contador = 1;
    int troca = 1;
    while(contador <= 5 && troca == 1){
        troca = 0;
        for(i = 0; i < n - 1; i++){
            if(lista[i] > lista[i+1]){
                aux = lista[i];
                lista[i] = lista[i+1];
                lista[i+1] = aux;
                troca = 1;
            }
        }
        contador = contador + 1;
    }
}

void bubble_sort2(int lista[], int n){
    int j, i, aux;
    for(j = 1; j <= 4; j++) {
        for(i = 4; i >= j; i--) {
            if(lista[i] < lista[i-1]) {
                aux = lista[i];
                lista[i] = lista[i-1];
                lista[i-1] = aux;
            }
        }
    }
}

void bubble_sort(int lista[], int n) {
    int i, aux, flag;
    flag = 1;
    while(flag == 1) {
        flag = 0;
        for(i = 0; i < n-1; i++) {
            if(lista[i] > lista[i+1]) {
                aux = lista[i];
                lista[i] = lista[i+1];
                lista[i+1] = aux;
                flag = 1;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    gera_vetor();
    
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    selection_sort(A, N);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Tempo de execucao: %f segundos\n", cpu_time_used);
    
    return 0;
}