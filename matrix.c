#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct {
	int nrow;
	int ncol;
	double **data;
} MATRIX;

MATRIX* allocM(int, int);
void freeM(MATRIX*);
void printM(MATRIX*);
MATRIX* addM(MATRIX*, MATRIX*);
MATRIX* subM(MATRIX*, MATRIX*);
MATRIX* deepcopyM(MATRIX*);
void randIntM(MATRIX*, int, int);
void randFloatM(MATRIX*, int, int);
int isNullM(MATRIX*);

int main(){
	MATRIX *matrix;
	MATRIX *mat1;
	MATRIX *mat2;

	matrix = allocM(6, 4);
	mat1 = allocM(6, 5);
	if(! isNullM(matrix) || ! isNullM(mat1)){
		for(int i = 0; i < 1; i++){
			randIntM(matrix, 19, 21);
			printM(matrix);
		}

		printM(mat1);

		freeM(matrix);
		freeM(mat1);
	}
}

MATRIX* allocM(int nrow, int ncol){
	if(nrow <= 0 || ncol <= 0){
		return NULL;
	}

	MATRIX *mat;
	mat = (MATRIX*)malloc(sizeof(MATRIX));
	if(mat == NULL){
		return NULL;
	}
	mat->nrow = nrow;
	mat->ncol = ncol;

	mat->data = (double**)malloc(sizeof(double*)*(mat->nrow));
	if(mat->data == NULL){
		return NULL;
	}

	for(int i = 0; i < (mat->nrow); i++){
		mat->data[i] = (double*)malloc(sizeof(double)*(mat->ncol));
		memset(mat->data[i], 0, sizeof(double)*(mat->ncol));
		if(mat->data == NULL){
			return NULL;
		}
	}

	return mat;
}

void freeM(MATRIX* m){
	for(int i = 0; i < (m->nrow); i++){
		free(m->data[i]);
	}
	free(m->data);
	free(m);
}

void randIntM(MATRIX* m, int min, int max){
	if(isNullM(m)){
		return;
	}

	int ncol = m->ncol;
	int nrow = m->nrow;

	struct timeval time;
	gettimeofday(&time, NULL);

	srand(time.tv_usec);
	for(int i = 0; i < nrow; i++){
		for(int j = 0; j < ncol; j++){
			m->data[i][j] = rand()%(max-min+1)+min;
		}
	}
	return;
}

void randFloatM(MATRIX* m, int min, int max){
	if(isNullM(m)){
		return;
	}

	int ncol = m->ncol;
	int nrow = m->nrow;

	struct timeval time;
	gettimeofday(&time, NULL);

	srand(time.tv_usec);
	for(int i = 0; i < nrow; i++){
		for(int j = 0; j < ncol; j++){
			m->data[i][j] = rand()%(max-min)+min + (float)rand()/RAND_MAX + FLT_MIN;
		}
	}
	return;

}

void printM(MATRIX* m){
	for(int i = 0; i < m->nrow; i++){
		if(i == 0){
			printf("┎ ");
		}else if(i == (m->nrow)-1){
			printf("┖ ");
		}else{
			printf("┃ ");	
		}

		for(int j = 0; j < (m->ncol); j++){
			printf("%8.3f ", m->data[i][j]);
		}

		if(i == 0){
			printf("┒");
		}else if(i == (m->nrow)-1){
			printf("┚");
		}else{
			printf("┃");	
		}

		printf("\n");
	}
}

MATRIX* deepcopyM(MATRIX* m){
	MATRIX* retm = allocM(m->nrow, m->ncol);
	retm->nrow = m->nrow;
	retm->ncol = m->ncol;
	for(int i = 0; i < m->nrow; i++){
		for(int j = 0; j < m->ncol; j++){
			retm->data[i][j] = m->data[i][j];	
		}
	}
	return retm;
}

MATRIX* addM(MATRIX* m1, MATRIX* m2){
	if(isNullM(m1) || isNullM(m2)){
		return NULL;
	}

	int ncol = m1->ncol;
	int nrow = m1->nrow;

	if((m1->ncol - m2->ncol) + (m1->nrow - m2->nrow) != 0){
		return NULL;
	}

	MATRIX* ansm = allocM(nrow, ncol);
	for(int i = 0; i < nrow; i++){
		for(int j = 0; j < ncol; j++){
			ansm->data[i][j] = m1->data[i][j] + m2->data[i][j];	
		}
	}
	return ansm;
}

MATRIX* subM(MATRIX* m1, MATRIX* m2){
	if(isNullM(m1) || isNullM(m2)){
		return NULL;
	}

	int ncol = m1->ncol;
	int nrow = m1->nrow;

	if((m1->ncol - m2->ncol) + (m1->nrow - m2->nrow) != 0){
		return NULL;
	}

	MATRIX* ansm = allocM(nrow, ncol);
	for(int i = 0; i < nrow; i++){
		for(int j = 0; j < ncol; j++){
			ansm->data[i][j] = m1->data[i][j] - m2->data[i][j];	
		}
	}
	return ansm;
}

MATRIX* mulM(MATRIX* m1, MATRIX* m2){
	if(isNullM(m1) || isNullM(m2)){
		return NULL;
	}

	if((m1->ncol - m2->nrow) != 0){
		return NULL;
	}

	int nrow = m1->nrow;
	int ncol = m2->ncol;


	MATRIX* ansm = allocM(nrow, ncol);
	for(int i = 0; i < nrow; i++){
		for(int j = 0; j < ncol; j++){
			ansm->data[i][j] = 0;
		}
	}
	return ansm;
}

MATRIX* transM(MATRIX* m1, MATRIX* m2){

}

MATRIX* loadM(FILE* fp){

}

void saveM(FILE* fp, MATRIX* m){

}

int isNullM(MATRIX* m){
	if(m == NULL){
		return 1;
	}
	if(m->data == NULL){
		return 1;
	}


	int ncol = m->ncol;
	int nrow = m->nrow;
	
	for(int i = 0; i < nrow; i++){
		for(int j = 0; j < ncol; j++){
			if(m->data[i] == NULL){
				return 1;
			}
		}
	}
	return 0;
}
