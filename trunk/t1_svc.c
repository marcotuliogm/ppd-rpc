#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "addit.h"

#define MAX_NR 1000

typedef char[30] text_t;
typedef char[3000] text_p;
typedef int	vet[MAX_NR]


typedef struct account {
    int ind;
    text_t user;
    text_t password;
    vet files;
}str_user;

typedef struct{
	text_t	titulo;
	text_t  data;
	text_t	hora;
	note	notas[MAX_NR];
	vet	permissoes;
	text_p	cont_inicial;	//conteudo inicial
}str_file;

typedef struct{
	text_t	titulo;
	text_t	user_edit;
	int 	em_uso;
	text_p	conteudo;
}str_note;


int *add_new_file(str_user *usr, str_file *fl){	//ret 1 se ok e 0 se erro.
	text_t arq;


	sprintf(arq, "%s.ppd", new_file);	//arquivos .ppd é o modelo para o nosso servidor.
	FILE *fp = fopen (arq, "a+");

	if(fp !=NULL){
		fprintf(fp, "%s;%s;%s;%s\n" fl->data, fl->hora, usr->user;fl->permissoes);
		fprintf(fp, "\n==== %s ====\n", fl->titulo);
		fprintf(fp, "\n%s\n\n", fl->cont_inicial);
		fprintf(fp, "------------------------------------------------------------------------------------------\n");
		//sai pronto, agora a baixo vem as notas do arquivo.
		fclose(fp);
		return 1;
	}

	else printf("ERRO INTESPERADO DO SISTEMA\n");
	return 0;

}

int *add_args_1_svc(record *rec, struct svc_file *clnt) {

    static int result;

    result = rec->first_num + rec->second_num;

    return ((int *) &result);
}

int *autentication_2_svc(account *user_account, struct svc_req *clnt){
	char line[80];
	sprintf(line, "%s%s", user_account->user, user_account->password);
	printf("%s\n\r", line);

	return ((int *) 0);
}

