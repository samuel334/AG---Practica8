#ifndef NPRMUTATION_H
#define NPRMUTATION_H

#include <stdio.h>
#include <string.h>

/*mutacion por insercion*/
void insertion(int c_lgth, int *indv, int v, int p);
/*mutacion por desplazamiento*/
void displacement(int c_lgth, int *indv, int index1, int index2, int p);
/*mutacion por intercambia reciproco*/
void exchange(int c_lgth, int *indv, int p1, int p2);
/*mutacion heuristica*/
void heuristic(int c_lgth, int *indv, int i_size, int *index, int (*fitness)(int lgth, const int *chromosome), int (*more_apt)(int f1, int f2));

#endif