/* Scrivere il programma che consente all’utente di comporre una frase selezionando le parole da un 
dizionario predefinito. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct{
	char testo[MAX];
	int lunghezza;
}parola;

int carica_dizionario(FILE *fpin, parola Diz[], int *n);
void stampa_dizionario(parola Diz[], int *n);
void componi_frase(parola Diz[], parola Frase[], int *n, int *m);
void trova_parola_lunga(parola Frase[], int *m, char max_len[]);

int main(){
	
	FILE *fpin;
	parola Diz[MAX];
	parola Frase[MAX];
	int status,n,m,i;
	char max_len[MAX];
	
	fpin=fopen("diz.txt","r");
	if(fpin==NULL){
		printf("Errore di apertura del file\n");
		exit(EXIT_FAILURE);
	}
	
	status=carica_dizionario(fpin,Diz,&n);
	if(status==0){
		printf("***ERRORE DI CARICAMENTO DATI***");
		exit(EXIT_FAILURE);
	}
	
	fclose(fpin);
	
	stampa_dizionario(Diz,&n);
	
	componi_frase(Diz,Frase,&n,&m);
	
	printf("\n");
	for(i=0;i<m;i++){
		printf("%s ",Frase[i].testo);
	}
	
	trova_parola_lunga(Frase,&m,max_len);
	printf("\n\nLa parola più lunga e': %s",max_len);
	
	return(0);
	
}

int carica_dizionario(FILE *fpin, parola Diz[], int *n){
	
	int status,i=0,error=0;
	parola data;
	
	while((status=fscanf(fpin,"%s",data.testo))!=EOF && i<MAX && error==0){
		if(status==1){
			data.lunghezza=strlen(data.testo);
			Diz[i]=data;
			i++;
		}else{
			error=1;
		}
	}
	
	*n=i;
	
	if(error==1){
		return(0);
	}else{
		return(1);
	}
	
}

void stampa_dizionario(parola Diz[], int *n){
	
	int i,tot_caratteri=0;
	
	for(i=0;i<*n;i++){
		tot_caratteri+=Diz[i].lunghezza;
	}
	
	printf(">>> Dizionario:\n");
	for(i=0;i<*n;i++){
		printf("%d: %s\n",i,Diz[i].testo);
	}
	printf(">>> Totale caratteri: %d\n",tot_caratteri);
	
}

void componi_frase(parola Diz[], parola Frase[], int *n, int *m){
	
	int input=1,i=0;
	
	printf("\nInserisci un numero che corrisponde ad una parola del dizionario\nPer terminare l'inserimento digitare un numero negativo\n");
	printf("I numeri possibili vanno da 0 a %d, numeri superiori ad esso verranno ignorati\n",*n-1);
	while(i<MAX){
		scanf("%d",&input);
		if(input>=0 && input<*n){
			strcpy(Frase[i].testo,Diz[input].testo);
			Frase[i].lunghezza=strlen(Frase[i].testo);
			i++;
		}else if(input<0){
			break;
		}
	}
	
	*m=i;
	
}

void trova_parola_lunga(parola Frase[], int *m, char max_len[]){
	
	int i,max;
	
	max=0;
	for(i=1;i<*m;i++){
		if(Frase[i].lunghezza > Frase[max].lunghezza){
			max=i;
		}
	}
	
	strcpy(max_len,Frase[max].testo);
	
}








































































































