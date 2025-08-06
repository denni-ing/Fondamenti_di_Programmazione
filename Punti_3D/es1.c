#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 20
#define ERROR -1

typedef struct{
	float x, y, z;
	char nome[N];
}punto;

int carica_dati(FILE *fpin, punto Point[], const int n);
void calcola_distanze(punto Point[], int *n, char lettera, float matrix[][N], int *z);
void stampa(float matrix[][N], int *z);

int main(){
	
	FILE *fpin;
	int status,n,z;
	punto Point[N];
	char lettera;
	float matrix[N][N];
	
	fpin=fopen("punti.txt","r");
	
	status=carica_dati(fpin,Point,N);
	if(status==ERROR){
		printf("Errore di apertura del file\n");
		exit(EXIT_FAILURE);
	}
	n=status;
	
	do {	
        printf("\nInserire una lettera minuscola dell'alfabeto: ");
    	scanf(" %c", &lettera);
    	if (lettera < 'a' || lettera > 'z') {
        	printf("Errore: Inserire una lettera minuscola valida.\n");
    	}
    }while(lettera < 'a' || lettera > 'z');
	
	calcola_distanze(Point,&n,lettera,matrix,&z);
	stampa(matrix,&z);
	
	fclose(fpin);
	
	return(0);
	
}

int carica_dati(FILE *fpin, punto Point[], const int n){
	
	int i=0,status;
	punto data;
	
	if(fpin==NULL){
		return(ERROR);
	}
	
	while((status=fscanf(fpin,"%f%f%f%s",&data.x,&data.y,&data.z,data.nome))!=EOF && i<n){
		if(status==4){
			Point[i]=data;
			i++;
		}else{
			break;
		}
	}
	
	return(i);
	
}

void calcola_distanze(punto Point[], int *n, char lettera, float matrix[][N], int *z){
	
	int i, j;
    *z = 0;
    
    for (i = 0; i < *n; i++) {
        if (strchr(Point[i].nome, lettera) != NULL) {
            (*z)++;
        }
    }

    for (i = 0; i < *z; i++) {
        for (j = 0; j < *z; j++) {
            matrix[i][j] = sqrt(pow(Point[i].x - Point[j].x, 2) + pow(Point[i].y - Point[j].y, 2) + pow(Point[i].z - Point[j].z, 2));
        }
    }
	
}

void stampa(float matrix[][N], int *z){
	
	int i,j;
	
	for(i=0;i<*z;i++){
		printf("\n");
		for(j=0;j<*z;j++){
			printf("%f",matrix[i][j]);
			if (j < *z - 1){
                printf("; ");
            }
		}
	}
	
}





















































































































