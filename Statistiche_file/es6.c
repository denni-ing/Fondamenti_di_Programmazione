#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TLEN 50
#define PLEN 4  //lunghezza pattern 4 + 1(\0)
#define STR_MAX 100
#define T 1
#define F 0

typedef struct{
	char testo[TLEN];
	int freq[PLEN];    
	int occur;   //valore binario per presenza di occorrenza
}statistica;

int leggi_seq(FILE *fpin, char testo[], char pattern[], int *len_str, int matrix[][TLEN]);
void calcola_stat(int matrix[][TLEN], int *len_str, statistica Stats[], int *index);
void stampa_stat(statistica Stats[], char pattern[], int *n);

int main(){
	
	char testo[TLEN]; //array per memorizzare una stringa
	char pattern[PLEN]={'A','B','C','D'}; //pattern noto
	int matrix[PLEN][TLEN]={0};
	int len_str; //lunghezza effettiva di una stringa
	int n; //numero di stringhe presenti nel file
	statistica Stats[STR_MAX];
	FILE *fpin;
	int i,status; //indici
	
	fpin=fopen("input.txt","r");
	if(fpin == NULL){
		printf("Errore di apertura del file\n");
		exit(EXIT_FAILURE);
	}
	
	fscanf(fpin,"%d",&n);
	if(n>100){
		n=100;
	}else if(n<=0){
		printf("***ERRORE: Numero di righe non valido***\n");
		exit(EXIT_FAILURE);
	}
	
	for(i=0;i<=n;i++){   //ripete azioni per ogni stringa
		status=leggi_seq(fpin,testo,pattern,&len_str,matrix);
		if(status==0){
			exit(EXIT_FAILURE);
		}
		if(i!=0){
			Stats[i].occur=1;
			strcpy(Stats[i-1].testo,testo);
			calcola_stat(matrix,&len_str,Stats,&i);
		}
	}
	
	stampa_stat(Stats,pattern,&n);

}

int leggi_seq(FILE *fpin, char testo[], char pattern[], int *len_str, int matrix[][TLEN]){
	
	// Utilizza fgets per leggere una riga intera
	char *status;
	status=fgets(testo, TLEN, fpin);
    if (status!= NULL && strlen(status)>1) {
        // Rimuovi il carattere di nuova riga alla fine della stringa
        int length = strlen(testo);
        if (length > 0 && testo[length - 1] == '\n') {
            testo[length - 1] = '\0';
        }
        *len_str = length;
        
        //inizio calcolo matrix
        int i,j;
        for(i=0;i<PLEN;i++){
        	for(j=0;j<*len_str;j++){
        		if(testo[j]==pattern[i]){
        			matrix[i][j]=T;
				}else{
					matrix[i][j]=F;
				}
			}
		}
        //fine calcolo matrix
        
    } else if(strlen(status)!=1){
        printf("Errore durante la lettura del file\n");
        return(F);
    }
    return(T);
}

void calcola_stat(int matrix[][TLEN], int *len_str, statistica Stats[], int *index){
	
	int i,j,patternfound,k=0,count;
	
	for(i=0;i<PLEN;i++){
		count=0;
		for(j=0;j<*len_str;j++){
			if(matrix[i][j]==1){
				count++;
			}
		}
		Stats[*index-1].freq[i]=count;
	}
	
	
	for(i=0;i<PLEN;i++){
		patternfound=0;
		for(j=k;j<*len_str;j++){
			if(matrix[i][j]==1){
				k=j+1;
			}
		}
		if(patternfound==0){
			Stats[*index-1].occur=0;
			break;
		}
	}
	
}

void stampa_stat(statistica Stats[], char pattern[], int *n){
	
	int i,j;
	
	for(i=0;i<*n;i++){
		printf("\nStatistica per la sequenza: %s\n",Stats[i].testo);
		for(j=0;j<PLEN;j++){
			printf("la frequenza di %c e': %d\n",pattern[j],Stats[i].freq[j]);
		}
		if(Stats[i].occur==1){
			printf("Occorrenza: SI\n");
		}
	}
	
}




























































































