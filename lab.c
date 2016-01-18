#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_l 100

int len(char* parola){
	int cont=0,i=0;
	while(parola[i]!='\0'){
		cont++;
		i++;
	}
	return cont;
}

int inside(char car, char* parola){
	int ver=0,i;
	for(i=0;i<len(parola);i++)
		if(car==parola[i])
			ver=1;
	return ver;
}

int anagramma(char* parola_a, char* parola_b){
	int lung_a=len(parola_a),lung_b=len(parola_b);
	int i;
	if(lung_a!=lung_b)
		return 0;
	for(i=0;i<lung_a;i++)
		if(!inside(parola_b[i],parola_a))
			return 0;
	return 1;
}

int sostit(char* parola_a, char* parola_b){
	int conta=0,i;
	int lung_a=len(parola_a);
	int lung_b=len(parola_b);
	if(lung_a!=lung_b)
		return 0;
	for(i=0;i<lung_a;i++)
		if(parola_b[i]!=parola_a[i])
			conta++;
	if(conta==1)
		return 1;
	return 0;
}

int agg(char*parola_a, char* parola_b){
	int lung_a,lung_b;
	int i=0,j=0,conta=0;
	lung_a=len(parola_a);
	lung_b=len(parola_b);
	if(lung_b!=lung_a+1)
		return 0;
	while(i<lung_b){
		if(parola_b[i]!=parola_a[j]){
			conta++;
			j--;
		}
		i++;
		j++;
	}
	if(conta!=1)
		return 0;
	return 1;
}

int elimin(char* parola_a,char* parola_b){
	int lung_a,lung_b;
	int i=0,j=0,conta=0;
	lung_a=len(parola_a);
	lung_b=len(parola_b);
	if(lung_b!=lung_a-1)
		return 0;
	while(i<lung_b && j<lung_a){
		if(parola_b[i]!=parola_a[j]){
			conta++;
			i--;
		}
		i++;
		j++;
	}
	if(conta!=1 && conta!=0)
		return 0;
	return 1;
}

int controllo(char* parola_a, char* parola_b){
	int conta_r=0;
	if(anagramma(parola_a,parola_b))
		conta_r++;
	if(sostit(parola_a,parola_b))
		conta_r++;
	if(agg(parola_a,parola_b))
		conta_r++;
	if(elimin(parola_a,parola_b))
		conta_r++;
	if(conta_r!=1)
		return 0;
	return 1;
}

int conta_parole(char* nome_file){
	FILE* fh;
	int conta=0,ret;
	char* parola;
	fh=fopen(nome_file,"r");
	parola=malloc(sizeof(char)*max_l);
	while(ret!=EOF){
		ret=fscanf(fh,"%s",parola);
		conta++;
	}
	fclose(fh);
	return conta-1;
}

int in(int num, int len, int *array){
	int i,cont=0;
	for(i=0;i<len;i++){
		if(num==array[i])
			return 1;
	}
	return 0;
}

int in_list(char* parola, int len, char** lista){
	int i;
	for(i=0;i<len;i++)
		if(strcmp(parola,lista[i])==0)
			return 1;
	return 0;
}

void risolvi(char* nome_file){
	FILE* fh;
	char* parole[conta_parole(nome_file)];
	char** parole_ord;
	char* last_poss;
	char* parola,*tmp;
	int ret,i=0,k=0,j=0,conta;
	int indici[conta_parole(nome_file)];
	int last_attempt=0,ver=1;
	fh=fopen(nome_file,"r");
	parola=malloc(sizeof(char)*max_l);
	conta=conta_parole(nome_file);
	ret=fscanf(fh,"%s",parola);
	i=0;
	while(ret!=EOF){
		parole[i]=malloc((sizeof(char)*len(parola))+1);
		strcpy(parole[i],parola);
		i++;
		ret=fscanf(fh,"%s",parola);
	}
	fclose(fh);
	parole_ord=malloc(sizeof(char*)*conta);
	for(i=0;i<conta;i++)
		parole_ord[i]=NULL;
	k=0;
	parole_ord[k]=malloc(sizeof(char)*len(parole[k])+1);
	strcpy(parole_ord[k],parole[k]);
	for(i=1;i<conta;i++)
		if(controllo(parole_ord[k],parole[i])){
			last_poss=parole[i];
		}
	for(i=0;i<conta;i++)
		indici[i]=0;
	while(parole_ord[conta-1]==NULL && ver){
		i=1;
		j=0;
		while(i<conta){
			if(controllo(parole_ord[k],parole[i]) && !in(i,conta,indici) && i>last_attempt){
				k++;
				last_attempt=0;
				parole_ord[k]=malloc(sizeof(char)*len(parole[i])+1);
				strcpy(parole_ord[k],parole[i]);
				indici[i]=i;
				i=0;
			}
			i++;
		}
		if(parole_ord[conta-1]==NULL && k>0){
			if(k==1 && strcmp(parole_ord[k],last_poss)==0)
				ver=0;
			for(i=0;i<conta;i++)
				if(strcmp(parole[i],parole_ord[k])==0){
					indici[i]=0;
					last_attempt=i;
				}
			free(parole_ord[k]);
			parole_ord[k]=NULL;
			k--;
		}
	}
	if(parole_ord[conta-1]==NULL)
		printf("Il labirinto di parole non è risolvibile\n");
	fh=fopen("solution.txt","w");
	for(i=0;i<conta;i++){
		fprintf(fh,"%s",parole_ord[i]);
		fprintf(fh,"%c",'\n');
	}
	fclose(fh);
	printf("E stato creato il file 'solution.txt' che contiene la soluzione del labirinto di parole\n");	
}

int main(){
	risolvi("parole.txt");
	return 0;
}
