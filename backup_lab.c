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
		if(!inside(parola_b[i],parola_a))
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
	while(i<lung_b){
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

void risolvi(char* nome_file){
	FILE* fh;
	char* parole[conta_parole(nome_file)];
	char** parole_ord;
	char* parola,*tmp;
	int ret,i=0,k=0,j=0,conta;
	fh=fopen(nome_file,"r");
	parola=malloc(sizeof(char)*max_l);
	conta=conta_parole(nome_file);
	ret=fscanf(fh,"%s",parola);
	while(ret!=EOF){
		parole[i]=malloc((sizeof(char)*len(parola))+1);
		strcpy(parole[i],parola);
		i++;
		ret=fscanf(fh,"%s",parola);
	}
	fclose(fh);
	parole_ord=malloc(sizeof(char*)*conta);
	parole_ord[k]=malloc(sizeof(char)*len(parole[k]));
	strcpy(parole_ord[k],parole[k]);
	for(i=0;i<conta;i++){
		j=1;
		printf("Prima %d\n",j);
		while(j<conta){
			printf("ora %d\n",j);
			if(controllo(parole_ord[k],parole[j])){
				k++;
				parole_ord[k]=malloc(sizeof(char)*len(parole[j])+1);
				printf("k %d\nj %d\n",k,j); 
			//	strcpy(parole_ord[k],parole[j]);
			}
			j++;
		}
	}
	//for(i=0;i<conta;i++)
		//printf("%s\n",parole_ord[i]);
}

int main(){
	int i;
	char** parole;
	risolvi("parole.txt");
	//for(i=0;i<conta_parole("parole.txt");i++){
	//	printf("%s\n",parole[i]);
	//}
	return 0;
}
