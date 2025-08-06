#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LEN 10
#define NAME_LEN 30
#define ABB_LEN 5
#define NUM 6
#define ERROR -1
#define Y "Y"
#define N "N"

typedef struct{
	int num_atom;
	char name[NAME_LEN];
	char abbrev[ABB_LEN];
	double mass_atom;
} elem;

int load_element(FILE *fpin, elem Element[], int n);
void print_table(elem Element[], int n);
double scan_request(char composto[], elem Element[], int len , int n);
double scan_table(char *atom_name, elem Element[], int n);

int main(){
	
	char composto[LEN];
	elem Element[NUM];
	FILE *fpin;
	int status=0;
	char yn[LEN];
	double result=0;
	
	//apertura e controllo file
	fpin=fopen("tavola_elementi.txt","r");
	if(fpin==NULL){
		printf("Errore nell'apertura del file");
		exit(EXIT_FAILURE);
	}
	
	
	status=load_element(fpin,Element,NUM);
	if(status!=ERROR){
		print_table(Element, NUM);
	}else{
		exit(EXIT_FAILURE);
	}
		
	do{
		printf("\nVuoi inserire un composto? digita Y(si) o N(no)\n");
		scanf("%s",yn);
		if(strcmp(yn,Y)==0){
			printf("Inserisci il composto: ");
			scanf("%s",composto);
			result=scan_request(composto,Element,LEN,NUM);
			if(result!=ERROR){
				printf("Peso atomico del composto %s : %lf",composto,result);
			}
			status=0;
		}else if(strcmp(yn,N)==0){
			status=1;
		}else{
			printf("   ***Errore nella digitazione***   \n");
			status=0;
		}
	}while(status!=1);
	
}

int load_element(FILE *fpin, elem Element[], int n){
	
	int status=0,i=0;
	elem data;
	
	while((status=fscanf(fpin,"%d %29s %3s %lf",&data.num_atom,data.name,data.abbrev,&data.mass_atom))!=EOF && i<n){
		if(status==4){
			Element[i]=data;  //copia dati file in array
			i++;
		}else if(status>=0 && status<4){
			status=0;
			break;
		}
	}
	
	if(status==0){
		printf("\n ***Errore nella lettura dei dati*** \n");
		return(ERROR);
	}else if(status!=EOF){
		printf("\n ***il file contiene troppi dati***\n");
		printf(" ***Usa solo i primi %d dati***\n",i);
		return(0);
	}else{
		printf("\n ***Lettura dati avvenuta con successo*** \n");
		return(0);
	}
	
	return(status);
	
}

void print_table(elem Element[], int n){
	
	int i;
	
	printf("Tavola degli elementi:\n");
	for(i=0;i<n;i++){
		printf("%d\t%s\t%s\t%lf\n",Element[i].num_atom,Element[i].name,Element[i].abbrev,Element[i].mass_atom);
	}
	
}

double scan_request(char composto[], elem Element[], int len , int n){
	
	int i=0,l;
	double result=0,scan_status;
	
	l=strlen(composto);
	
	while(i<l){
		
		char atom_name[len];
	    int atom_quantity=1;
	    int j=0;
	    
	    if(i<len && isupper(composto[i])!=0){
	    	atom_name[j++] = composto[i++];
		}
		
		while(i < len && (islower(composto[i]))!=0){ //Lettura delle lettere minuscole dopo la prima maiuscola
        	atom_name[j++] = composto[i++];
		}
		
		atom_name[j] = '\0';
        
        if(i < len && isdigit(composto[i])){  //lettura numeri
        	atom_quantity = composto[i++] - '0';
		}
        
        if (atom_quantity == 0) {
            atom_quantity = 1;  // Se la quantità non è specificata, assume 1
        }
		
		scan_status=scan_table(atom_name,Element,n);
		if(scan_status==ERROR){
			result=ERROR;
			break;
		}else{
			result+=atom_quantity*scan_status;
		}
	}
	
	return(result);
	
	
}

double scan_table(char *atom_name, elem Element[], int n){
	
	int i,status;
	double target;
	
	for(i=0;i<n;i++){
		if(strcmp(atom_name,Element[i].abbrev)==0){
			target=Element[i].mass_atom;
			status=0;
			break;
		}else{
			status=1;
		}
	}
	
	if(status!=0){
		printf("\n***Composto non trovato***\n");
		return(ERROR);
	}else{
		return(target);
	}
	
}



































