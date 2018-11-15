#include "nprmutation.h"

/********************************************************************************************************
					F U N C I O N E S 	A U X I L I A R E S

********************************************************************************************************/
/*siguiente indice ciclico*/
int next(int act, int min, int max){
	return (act==max ? min : act + 1);
}

/*intercambia valores*/
void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*Funcion auxiliar para permutacion heuristico.
Genera permutaciones de los genes seleccionados, y evalua y selecciona al mejor*/
int permute_n_evaluate(int pn, int *best_f, int at, int i_size, int *index, int *best, int c_lgth, int *indv, int (*fitness)(int lgth, const int *chromosome), int (*more_apt)(int f1, int f2)){
	int i, f;
	if(at==(i_size - 1)){
		/*evaluar permutacion*/
		if(pn!=1){
			f = fitness(c_lgth, indv);
			if(pn==2){
				for(i = 0;i<i_size;i++) best[i] = indv[index[i]];
				*best_f = f;
			}else{
				if(more_apt(f, *best_f)>0){
					for(i = 0;i<i_size;i++) best[i] = indv[index[i]];
					*best_f = f;
				}
			}
		}
		return (++pn);
	}else{
		for(i = at;i<i_size;i++){
			swap(&indv[index[at]], &indv[index[i]]);
			pn = permute_n_evaluate(pn, best_f, at + 1, i_size, index, best, c_lgth, indv, fitness, more_apt);
			swap(&indv[index[at]], &indv[index[i]]);
		}
		return pn;
	}
}

/********************************************************************************************************
					F U N C I O N E S 	P R I N C I P A L E S

********************************************************************************************************/
/*mutacion por insercion*/
void insertion(int c_lgth, int *indv, int v, int p){
	if(v==p || v<0 || v>=c_lgth || p<0 || p>=c_lgth) return;
	int i = p, act = indv[v];
	while(i!=v){
		swap(&indv[i], &act);
		i = v>p ? i + 1 : i - 1;
	}
	indv[i] = act;
}

/*mutacion por desplazamiento*/
void displacement(int c_lgth, int *indv, int index1, int index2, int p){
	if(p==index1 || index1<0 || index1>=c_lgth || index2<0 || index2>=c_lgth  || p<0 || p>=c_lgth) return;
	int sa_size = index2 - index1 + 1, t_size = index2 - index1 + 2;
	int subarray[sa_size], temp[t_size];
	int i = p, si = 0, fi_t = 0, li_t = 0;
	memcpy(subarray, &indv[index1], sizeof(int)*sa_size);
	for(si = 0;si<sa_size;si++){
		if(i<index1 || i>index2){
			temp[li_t] = indv[i];
			li_t = next(li_t, 0, t_size - 1);
		}
		indv[i] = subarray[si];
		i = next(i, 0, c_lgth - 1);
	}
	while(i!=p){
		if(i<index1 || i>index2){
			temp[li_t] = indv[i];
			li_t = next(li_t, 0, t_size - 1);
		}
		indv[i] = temp[fi_t];
		fi_t = next(fi_t, 0, t_size - 1);
		i = next(i, 0, c_lgth - 1);
	}
}

/*mutacion por intercambia reciproco*/
void exchange(int c_lgth, int *indv, int p1, int p2){
	if(p1==p2 || p1<0 || p1>=c_lgth || p2<0 || p2>=c_lgth) return;
	swap(&indv[p1], &indv[p2]);
}

/*mutacion heuristica*/
void heuristic(int c_lgth, int *indv, int i_size, int *index, int (*fitness)(int lgth, const int *chromosome), int (*more_apt)(int f1, int f2)){
	if(i_size>c_lgth) return;
	int i, value[i_size], f;
	permute_n_evaluate(1, &f, 0, i_size, index, value, c_lgth, indv, fitness, more_apt);
	for(i = 0;i<i_size;i++){
		indv[index[i]] = value[i];
	}
}
