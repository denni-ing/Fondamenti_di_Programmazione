/* Scrivere un programma che legge il file e determina le tratte aeree per le quali esistono sia il volo di
andata sia il volo di ritorno. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 200
#define LEN 4

typedef struct{
	char partenza[LEN];
	char arrivo[LEN];
}elem;

int load_data(FILE *fpin, elem Voli[], int *n);
void tratte_andata_ritorno(elem Voli[], int *n, elem Tratte[], int *k);
void visualizza_tratte(elem Tratte[], int *k);

int main(){
	
	FILE *fpin;
	int status,i,n,k;
	elem Voli[N];
	elem Tratte[N];

	fpin=fopen("input.txt","r");  //apertura file input.txt
	if(fpin==NULL){
		printf("Errore nell'apertura del file\n");
		exit(EXIT_FAILURE);
	}
	
	status=load_data(fpin,Voli,&n);
	if(status==1){
		printf("***Errore nel caricamento***\n");
		printf("Verranno visualizzati soltanto i primi 200 voli\n");
	}
	
	tratte_andata_ritorno(Voli,&n,Tratte,&k);
	visualizza_tratte(Tratte,&k);
	
	fclose(fpin); //chiusura file input.txt
	
	return(0);
	
}

int load_data(FILE *fpin, elem Voli[], int *n){
	
	int i=0, status;
	elem data;
	
	while((status=fscanf(fpin,"%s %s",data.partenza,data.arrivo))!=EOF && i<N){
		if(status==2){
			Voli[i]=data;
			i++;
		}else{
			status=1;
			break;
		}
	}
	
	*n=i;
	
	if(status!=1){
		return(0);
	}else{
		return(1);
	}
	
}


void tratte_andata_ritorno(elem Voli[], int *n, elem Tratte[], int *k){
	
	int i,j,p=0;
	elem data;
	
	for(i=0;i<*n-1;i++){
		strcpy(data.partenza,Voli[i].arrivo);
		strcpy(data.arrivo,Voli[i].partenza); //copio la tratta inversa del volo nella variabile data
		for(j=i;j<*n;j++){                    //controllo se la tratta inversa è uguale ad una delle tratte presenti
			if(strcmp(data.partenza,Voli[j].partenza)==0 && strcmp(data.arrivo,Voli[j].arrivo)==0){
				Tratte[p]=data;               //popolo il vettore delle tratte di ritorno
				p++;
			}
		}
	}
	
	*k=p;
	
}

void visualizza_tratte(elem Tratte[], int *k){
	
	int i;
	
	printf("\nNumero di tratte di andata e ritorno: %d\n",*k);
	for(i=0;i<*k;i++){
		printf("%s\t%s\n",Tratte[i].partenza,Tratte[i].arrivo);
	}
	
}






































































