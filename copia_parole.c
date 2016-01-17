#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 20

int main(){
	FILE *fp,*new;
	int ret;
	char* parola;
	parola=malloc(sizeof(char)*MAX_L);
	fp=fopen("parole.txt","r");
	new=fopen("prova.txt","w");
	if(fp==NULL)
		return 0;
	while(ret!=EOF){
		ret=fscanf(fp,"%s",parola);
		fprintf(new,"%s",parola);
		fprintf(new,"%c",'\n');
	}
	fclose(fp);
	fclose(new);
	return 0;

}
