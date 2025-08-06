#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "mylib.h"

#define MAX_UNITS 6  //massimo elementi nell'array Element
#define LEN 10       //lunghezza massima del composto
#define LEN_NAME 30  //lunghezza massima nomi struttura
#define NOT_FOUND -1 //constante utilizzata per errori
#define RESULT_ERROR -1000000 //constante utilizzata per errore calcolo atomo non trovato
#define Y "Y"
#define N "N"
#define N 100

typedef struct{
	int num_atom;
	char name[LEN_NAME];
	char abbrev[LEN];
	double mass_atom;
} elem;

int load_elem(FILE *fpin, elem Element[], int n){
	
	int status,i=0;
	elem data;
	
	while((status=fscanf(fpin,"%d %29s %3s %lf",&data.num_atom,data.name,data.abbrev,&data.mass_atom))!=EOF && i<n){
		if(status==4){
			Element[i]=data;
			i++;
		}else if(status>=0 && status<4){
			status=0;
			break;
		}
		
	}
	
	if(status==0){
		printf("\n ***Errore nella lettura dei dati*** \n");
		return(NOT_FOUND);
	}else if(status!=EOF){
		printf("\n ***il file contiene troppi dati***\n");
		printf("***Usa solo i primi %d dati\n",i);
		return(0);
	}else{
		printf("\n ***Lettura dati avvenuta con successo*** \n");
		return(0);
	}
	
}

void print_table(elem Element[], int n){
	
	int i=0;
	
	printf("TAVOLA DEGLI ELEMENTI:\n");

	do{
		printf("%d\t %s\t %s\t %lf\n",Element[i].num_atom,Element[i].name,Element[i].abbrev,Element[i].mass_atom);
		i++;
	}while(i<n);
	
	printf("\n");
	
}

float scan_request(const char *composto, elem Element[], int n, int l){
	
	float result=0;
	int status,i=0,len;
	char target;
	float scan_status;
	
	len=strlen(composto);
		
	while(i<len){
		
		char atom_name[l];
	    int atom_quantity=1;
	
		// Leggi il nome dell'atomo
        int j = 0;
        
        if(i<len && (isupper(composto[i]))!=0){
        	atom_name[j++] = composto[i++];
		}
        
        while(i < len && (islower(composto[i]))!=0){
        	atom_name[j++] = composto[i++];
		}
		
		atom_name[j] = '\0';
        
        if(i < len && isdigit(composto[i])){
        	atom_quantity = composto[i++] - '0';
		}
        
        if (atom_quantity == 0) {
            atom_quantity = 1;  // Se la quantità non è specificata, assume 1
        }
        
        printf("%s ",atom_name);
        printf("%d\n",atom_quantity);
        
        scan_status=scan_table(atom_name,Element);
        if(scan_status==NOT_FOUND){
        	result=RESULT_ERROR;
        	break;
		}else{
			result+=atom_quantity*scan_status;
		}	
    }
    
	return(result);
	
}

float scan_table(const char *atom_name, elem Element[]){
	
	int i=0,found=0;
	
	for (i = 0; i < MAX_UNITS; i++) {
        if (strcmp(Element[i].abbrev, atom_name) == 0) {
            found=1;
            return Element[i].mass_atom;
        }
    }
    
    if(found==0){
    	printf("Atomo non trovato: %s\n", atom_name);
        return NOT_FOUND;
	}
	
}


























