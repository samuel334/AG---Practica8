#include "nprmutation.h"
#include <stdlib.h>
#include <time.h>

/*funcion de aptitud. La funcion solo se utiliza para pruebas, no tiene ningun significado especial*/
int fitness(int size, const int chromosome[size]){
	return (rand()%(1000 + 1));	//regresa un numero aleatorio entre 0 y 1000
}

/*Funcion para determinar cual es el individuo mas apto de dos individuos, se utiliza 
la aptitud de los individuos para el calculo. Si f1 es mas apto que f2 regresa 1, si f1
es menos apto que f2 regresa -1, y si tienen la misma aptitud regresa 0.*/
int more_apt(int f1, int f2){
	if(f1>f2){
		return 1;
	}else if(f2>f1){
		return -1;
	}else{
		return 0;
	}
}

/*funcion para barajear los elemntos de un array*/
void shuffle(int size, int array[size]){
	int i, j, temp;
	for(i = 0;i<(size - 1);i++){
		j = rand()%((size - 1) - i + 1) + i;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

/*generar poblacion inicial de manera aleatoria, la representacion del cromosoma es para permutaciones*/
void generatePopulation(int p_lgth, int c_lgth, int population[p_lgth][c_lgth]){
	int i, j, gen;
	for(i = 0;i<p_lgth;i++){
		for(j = 0;j<c_lgth;j++){
			population[i][j] = j + 1;	//fijar valor de gen de individuo i
		}
		shuffle(c_lgth, population[i]);
	}
}

/*mutar poblacion*/
void mutation(int p_lgth, int c_lgth, int individual[p_lgth][c_lgth]){
	int i, j, r, temp; //variables auxiliares
	int size, index[c_lgth];	//numero de genes a tomar, y arreglo con los indices de los genes a tomar para la mutacion
	for(i = 0;i<c_lgth;i++) index[i] = i;
	for(i = 0;i<p_lgth;i++){
		/*imprimier en pantalla el individuo a mutar*/
		printf("individuo: ");
		for(j = 0;j<c_lgth;j++) printf("%d ", individual[i][j]);
		printf("\t|\t");
		/*generar aleatoriamente el numero de genes a tomar*/
		size = (rand()%((c_lgth - 1) - (2) + 1)) + (2);
		/*seleccionar aleatoriamente los genes a tomar*/
		for(j = 0;j<size;j++){
			r = rand()%((c_lgth - 1) - j + 1) + j;
			temp = index[j];
			index[j] = index[r];
			index[r] = temp;
		}
		/*imprimir en pantalla los genes seleccionados*/
		printf("genes: ");
		for(j = 0;j<c_lgth;j++) (j<size) ? printf("%d", individual[i][index[j]]) : printf(" ") ;
		/*mutar individuo*/
		heuristic(c_lgth, individual[i], size, index, fitness, more_apt);	//mutacion heuristica
		/*imprimir individuo mutado*/
		printf("\t|\tmutacion: ");
		for(j = 0;j<c_lgth;j++) printf("%d ", individual[i][j]);
		printf("\n");
	}
}

int main(int argc, char *argv[]){
	if(argc!=3) exit(1);
	int p_lgth = atoi(argv[1]); //numero de individuos por generacion
	int c_lgth = atoi(argv[2]);	//tamaño del cromosoma
	if(p_lgth<0 || p_lgth%2 || c_lgth<3) exit(1);
	srand(time(NULL));
	int individual[p_lgth][c_lgth];	//poblacion
	/*generar poblacion inicial*/
	generatePopulation(p_lgth, c_lgth, individual);
	/*mutar poblacion*/
	mutation(p_lgth, c_lgth, individual);
	return 1;
}
