/* DENNI LUCHETTI 18/12/2023
Scrivere il programma che calcola il peso atomico di un composto */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_UNITS 6  //massimo elementi nell'array Element
#define LEN 10       //lunghezza massima del composto
#define LEN_NAME 30  //lunghezza massima nomi struttura
#define NOT_FOUND -1 //constante utilizzata per errori
#define RESULT_ERROR -1000000 //constante utilizzata per errore calcolo atomo non trovato
#define Y "Y"
#define N "N"

typedef struct{
	int num_atom;
	char name[LEN_NAME];
	char abbrev[LEN];
	double mass_atom;
} elem;

main(){
	
	elem Element[MAX_UNITS];
	char composto[LEN];
	FILE *fpin;
	int status,i;
	char yn[LEN];
	float result;
	
	fpin=fopen("tavola_elementi.txt","r");
	
	if(fpin==NULL){
		printf("Errore nell'apertura del file");
		exit(EXIT_FAILURE);
	}
	
	status=load_elem(fpin, Element, MAX_UNITS);
	fclose(fpin);
	if(status==NOT_FOUND){ //controllo errore di lettura
		exit(EXIT_FAILURE);
	}else{
		printf("\n");
		print_table(Element, MAX_UNITS); //stampa tavola elementi
	}
	
	i=0;
	do{
		printf("Vuoi inserire un composto? digita %s(si) o %s(no)\n",Y,N);
		scanf("%s",yn);
		if(strcmp(yn,Y)==0){
			printf("Inserisci il composto: ");
			scanf("%s",composto);
			i++;
			status=1;
			result=scan_request(composto, Element, MAX_UNITS, LEN_NAME);
			if(result==RESULT_ERROR){
				continue;
			}else{
				printf("Peso atomico del composto %s : %f\n",composto,result);
			}
		}else if(strcmp(yn,N)==0){
			status=0;
		}else{
			printf("   ***Errore nella digitazione***   \n");
			printf("Vuoi inserire un composto? digita Y(si) o N(no)\n");
			status=1;
		}
	}while(status==1);
	
	return 0;
	
}
