/* LUCHETTI DENNI
Scrivere un programma per valutare un esame composto da nq domande (con nq compreso tra 5 e 
50) a scelta multipla (a,b,c,d) e notificare le domande sbagliate più frequentemente */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ANSWER 50
#define N_STUDENTS 100

int fget_answer(FILE *fpin, int *nq, char corr_answer[], int id_students[], char answer[][MAX_ANSWER]);
void get_wrong( char corr_answer[], char answer[][MAX_ANSWER], float wrong[], const int *nq, const int *n_students);
void fwrite_report(FILE *fpout, char corr_answer[], float wrong[], const int *nq, const int *n_students);

int main(){
	
	FILE *fpin, *fpout;
	int nq,i,j,n_students;
	char corr_answer[MAX_ANSWER];
	int id_students[N_STUDENTS];
	char answer[N_STUDENTS][MAX_ANSWER];
	float wrong[MAX_ANSWER];
	
	//apertura file lettura
	fpin=fopen("examdat.txt","r");
	
	if(fpin==NULL){
		printf("Errore nell'apertura del file\n");
		exit(EXIT_FAILURE);
	}

	n_students=fget_answer(fpin,&nq,corr_answer,id_students,answer);
	fclose(fpin);
	
	printf("RISPOSTE DEGLI STUDENTI:\n");
	for(i=0;i<n_students;i++){
		printf("%d\t",id_students[i]);
		for(j=0;j<nq;j++){
			printf("%c\t",answer[i][j]);
		}
		printf("\n");
	}
	
	get_wrong(corr_answer,answer,wrong,&nq,&n_students);
	
	fpout=fopen("report.txt","w");
	fwrite_report(fpout, corr_answer, wrong,&nq,&n_students);
	fclose(fpout);
	
}

int fget_answer(FILE *fpin, int *nq, char corr_answer[], int id_students[], char answer[][MAX_ANSWER]){
	
	int status,j=0,count=0;
	int n=0;

	status=fscanf(fpin,"%d %c%c%c%c%c",&n,&corr_answer[0],&corr_answer[1],&corr_answer[2],&corr_answer[3],&corr_answer[4]);
	if(status!=6){
		printf("***Errore lettura***\n");
    }
    
    *nq=n;
	
	while((status=fscanf(fpin,"%d %c %c %c %c %c",&id_students[j],&answer[j][0],&answer[j][1],&answer[j][2],&answer[j][3],&answer[j][4]))!=EOF && j<N_STUDENTS){
		j++;
		count++;
	}
	
	printf("CARICAMENTO DATI AVVENUTO\n\n");
	
	return(count);
	
}

void get_wrong( char corr_answer[], char answer[][MAX_ANSWER], float wrong[], const int *nq, const int *n_students){
	
	int i,j,status=0;
	
	for(i=0;i<*nq;i++){
		status=0;
		for(j=0;j<*n_students;j++){
			if(corr_answer[i]!=answer[j][i]){
				status++;
			}
		}
		
		wrong[i]=((float)status/(*n_students))*100;  
	}
	
}

void fwrite_report(FILE *fpout, char corr_answer[], float wrong[], const int *nq, const int *n_students){
	
	int i;
	
	fprintf(fpout,"Exam Report\nQuestion\t1\t2\t3\t4\t5\n");
	
	fprintf(fpout,"Answer\t\t");
	for(i=0;i<*nq;i++){
		fprintf(fpout,"%c\t",corr_answer[i]);
	}
	fprintf(fpout,"\n");
	
	fprintf(fpout,"Wrong(%%)\t");
	for(i=0;i<*nq;i++){
		fprintf(fpout,"%d\t",(int)wrong[i]);
	}
	fprintf(fpout,"\n");
	
	printf("\nCOPIA DATI EFFETTUATA");
	
}


























