/* addit.c client code for the example application */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "defines.h"
#include "addit.h"

#define SERVER "127.0.0.1"
#define MENU_STR_SIZE 30


CLIENT *cl_docs = NULL;
file *file_open;	//id do documento aberto...
account *usr_now;

int user = ERR_NOT_AUTHENTICATED;
int open_file = ERR_NOT_EXIST;

int auth(){
	int answer;
	int retry = 3;
    CLIENT *cl_auth;
	account *user_account = (account *) malloc(sizeof(account));

	if (!(cl_auth = clnt_create(SERVER, DOCS, ACCOUNT_MANAGER, "tcp"))){
        clnt_pcreateerror(SERVER);
        return ERR_NOT_CONNECTED;
    }
	do {
		printf("------------------------------ USER LOGIN ------------------------------\n\r");
		printf("User: ");
		scanf("%s", user_account->login);
		printf("Password: ");
		scanf("%s", user_account->password);

		answer = *authentication_2(user_account, cl_auth);
//		printf("answer %d\n\r", answer);
	    if (answer < 0) {
	        printf("User or password wrong: try again\n\r");
			retry--;
	    }
	} while ((retry > 0) & (answer < 0));
	if (retry == 0){
		clnt_destroy(cl_auth);
        printf("Number of retries exceeded\n\r");
		return ERR_NOT_AUTHENTICATED;
	}
	user = answer;
	clnt_destroy(cl_auth);
	return 0;
}

int criar_nota()
{
	data_t	nt_add;
	file *fp = (file *) malloc(sizeof(file));
	note *nota = (note *) malloc(sizeof(note));;	
	char conf[10];
	int grv_note;
	int nro_nota;
	
	nota->num_note = *createnewnote_1(&open_file, cl_docs);
	nota->num_file = open_file;

		printf("Titulo: ");
		getchar();
		scanf("%[0-9 A-Z a-z]", nota->title);

		printf("Conteudo: ");
		getchar();
		scanf("%[0-9 A-Z a-z]", nota->conteudo);
		nota->user_edit = user;
		nota->estou_em_uso = 0;
	
	return *savenote_1(nota, cl_docs);

}





int add_new_file(){	//ret 1 se ok e 0 se erro.

	file *fl = (file *) malloc(sizeof(file));;
	int num_fl;
	char cf[5];

/*
	if (!(cl_docs = clnt_create(SERVER, DOCS, DOCUMENTS_MANAGER,"tcp"))) { 
        	clnt_pcreateerror(SERVER); 
        	return ERR_NOT_CONNECTED; 
    	}
*/

	num_fl = *reqnewfile_1(&user, cl_docs);

	printf("Informe o Titulo: ");
	getchar();
	scanf("%[0-9 A-Z a-z]", fl->title);
	printf("------------------------------------------------------------------------------------------\n");
	printf("Conteudo: \n");
	getchar();
	scanf("%[0-9 A-Z a-z]", fl->conteudo_inicial);

	fl->tam_note = 0;
	fl->num_link = num_fl;
	fl->permissoes[0] = user;
	fl->count_permission = 1;

	open_file = *createnewfile_1(fl, cl_docs);
}

int show_my_docs(){
	Files *st_files = NULL;
	int i;
	printf("Teste\n\r");
	st_files = showdocspermission_1(&user, cl_docs);
	printf("\n\r------ Lista de Documentos ------\n\r");
	if (st_files != NULL){
		printf("Numero de documentos %d\n\r", st_files->max_files);
		printf("NUM | Titulo \n\r");
		for (i=0; i<st_files->max_files; i++){
			printf("%-3d | %s\n\r", st_files->doc[i].num_link, st_files->doc[i].title);
		};
	}
	printf("---- FIM Lista de Documentos ----\n\r\n\r");

}

int show_users(){
	Accounts *st_account = NULL;
	int i;
	st_account = showusers_1(&i, cl_docs);	
	printf("\n\r------ Lista de usuarios ------\n\r");
	for (i=0; i<st_account->max_users; i++){
		printf("%d %s\n\r", i+1, st_account->user[i].login);
	};
	printf("---- FIM Lista de usuarios ----\n\r\n\r");
}

int open_document(){
	int per, id;
	per = 0;
	intret *param = (intret *) malloc(sizeof(intret));
	param->param2 = user;
	show_my_docs();
	do{
		printf("Informe o ID do documento.");
		scanf("%d", &param->param1);
		per = *checkper_1(param, cl_docs); //erro unary *
		printf("permissao %d\n\r", per);
		per = 1;
	}while(!per);
	open_file = param->param1;
	return 0;
}

void associar_usuario(){
	int ret;
	intret *param = (intret *) malloc(sizeof(intret));
	show_users();
		printf("Informe o ID do usuario.");
		scanf("%d", &param->param2);
	// verificar se usuario existe
	param->param1 = open_file;
	ret = *setpermission_1(param, cl_docs);	
}

void show_properties(){
	file *document = (file *) malloc(sizeof(file));
	document = getdocument_1(&open_file, cl_docs);
	printf("Titulo: %s\n\r", document->title);
	printf("Data:   %s\n\r", document->date );
	printf("Hora:   %s \n\r", document->hour );
	printf("Usuarios com permissao: %d\n\r", document->count_permission);
	printf("Resumo: %s\n\r", document->conteudo_inicial);
}

void show_document(){
	int i;
	file *document = (file *) malloc(sizeof(file));
	document = getdocument_1(&open_file, cl_docs);
	printf("Titulo: %s\n\r", document->title);
	printf("Data:   %s\n\r", document->date );
	printf("Hora:   %s \n\r", document->hour );
	printf("Usuarios com permissao: %d\n\r", document->count_permission);
	printf("Resumo: %s\n\r", document->conteudo_inicial);
	for (i=0; i<document->tam_note; i++){
		printf("\n\r %s \n\r %s \n\r", 
					document->notes[i].title,
					document->notes[i].conteudo
					);
	}
}

void show_menu_docs(){
	int volta = 0,
		option,
		i, usr_add;

	//escolher doc aqui...........................

	while (!volta){
		for(i = 0; MENU_DOCS[i].desc!=NULL; i++){
			printf("%d %s\n\r", i+1, MENU_DOCS[i].desc);
		}
	
		printf("Escolha uma opcao DOCUMENTOS: ");
		scanf("%d", &option);
		switch (option){
			case ITEM1:
					show_users();
					associar_usuario();
					break;
			case ITEM2:
					show_properties(); //open_doc global
					break;
			case ITEM3:
					criar_nota();
					break;
			case ITEM4:
					break;
			case ITEM5:
					break;
			case ITEM6:
					show_document();
					break;
			case ITEM7:
					volta = 1;
					break;
		}
	}
}

main(int argc, char *argv[]) {
//    CLIENT *cl, *cl_auth;
//    int answer;
	int i, 
		option,
		exit=0;
	int ret;

	ret = auth();
	if (ret != 0){
		printf("ret: %d\n\r", ret);
		return ret;
	}

/////////////////////////////////////////////////////////////////////////////////////
	if (!(cl_docs = clnt_create(SERVER, DOCS, DOCUMENTS_MANAGER,"tcp"))) { 
        	clnt_pcreateerror(SERVER); 
        	return ERR_NOT_CONNECTED; 
    	}
/////////////////////////////////////////////////////////////////////////////////////


	while (!exit){
		for(i = 0; MENU[i].desc!=NULL; i++){
			printf("%d %s\n\r", i+1, MENU[i].desc);
		}
	
		printf("Escolha uma opcao: ");
		scanf("%d", &option);
		switch (option){
			case ITEM1:
					add_new_file(); //usuario sera global apos a autenticacao
					break;
			case ITEM2:
					open_document(); //Variavel global com indice do documento aberto
					show_menu_docs();
					break;
			case ITEM3:
					show_my_docs();
					printf("Pressione uma tecla para continuar\n\r");
//					scanf("%d", &option);
					getchar();					
					break;
			case ITEM4:
//					show_search();
					break;
			case ITEM5:
					printf("Show Users\n\r");
					show_users();
					break;
			case ITEM6:
					exit = 1;
					break;
		}
	}	
	clnt_destroy(cl_docs);
/*	record *rec = (record *) malloc(sizeof(record));

    if (argc != 4) {
        printf("Usage: %s hostname <operando> <operando>\n", argv[0]); 
		printf("Onde:\n");
		printf("        <hostname> hostname ou endereco IP do servidor.\n");
		printf("        <operando> deve ser um n�mero inteiro.\n");
        exit (1);
	}

	if (!(cl = clnt_create(argv[1], ADDITPROG, ADDITVERS, "tcp"))) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

	rec->first_num = atoi(argv[2]);
	rec->second_num = atoi(argv[3]);
	answer = *add_args_1(rec, cl);
	printf("answer %d\n\r", answer);
	if (answer < 0) {
		printf("error: could not produce meaningful results\n\r");
		exit(1);
	}
	if (answer >= 0) {
		printf("OK\n\r");
	}
	*/
}

