/* addit.c client code for the example application */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "addit.h"

#define SERVER "127.0.0.1"


enum ERROR{
	ERR_NOT_CONNECTED = -1,
	ERR_NOT_AUTHENTICATED = -2,
};


int auth(){
	int answer;
	int retry = 3;
    CLIENT *cl_auth;
	account *user_account = (account *) malloc(sizeof(account));
	

	if (!(cl_auth = clnt_create(SERVER, ADDITPROG, ACCOUNT_MANAGER,"tcp"))) { 
        clnt_pcreateerror(SERVER); 
        return ERR_NOT_CONNECTED; 
    }
	do {
		printf("------------------------------ USER LOGIN ------------------------------\n\r");
		printf("User: ");
		scanf("%s", user_account->user);
		printf("Password: ");
		scanf("%s", user_account->password);
	
		answer = *authentication_2(user_account,cl_auth);
		printf("answer %d\n\r", answer);
	    if (answer < 0) { 
	        printf("User or password wrong: try again\n\r");
			retry--;
	    }
	} while ((retry > 0) & (answer != 0));
	if (retry == 0){
		clnt_destroy(cl_auth);
        printf("Number of retries exceeded\n\r");
		return ERR_NOT_AUTHENTICATED;
	}
	clnt_destroy(cl_auth);
	return 0;
}


int criar_nota(int num_fl, account *usr)
{
	data_t	nt_add;
	file *fp;
	note *nota;	
	char conf[10];
	int grv_note;
	int nro_nota;

/////////////////////////////////////////////////////////////////////////////////////
	CLIENT *cl_auth;
	if (!(cl_auth = clnt_create(SERVER, ADDITPROG, ACCOUNT_MANAGER,"tcp"))) { 
        	clnt_pcreateerror(SERVER); 
        	return ERR_NOT_CONNECTED; 
    	}
/////////////////////////////////////////////////////////////////////////////////////


	fp = arqedit_2(&num_fl, cl_auth); //

	//em uso.
	nro_nota = notauso_2(num_fl, cl_auth);

	printf("Arquivo de edicao: %s.\n", fp->title);
	printf("Ultima alteracao: %s -  %s\n", fp->date, fp->hour);

	nota->num_link = num_fl;

	while(1){
		strcpy(conf, "no"); //confirmação de envio.
		//parametros nota.
		printf("Titulo: ");
		scanf(nota->title, "&s");
		strcpy(nota->user_edit, usr->user);
		nota->estou_em_uso = 0;	//0 porque é criação, ou seja, inicialização.

		printf("Conteudo: ");
		scanf(nt_add, "&s");

		strcpy(nota->conteudo, nt_add);	//grava nota.

		printf("Confirmar nota: <yes,no>\n");
		scanf(conf, "&s");

		if(strcmp(conf,"yes")!=0) continue;

		//senão grava dados.
			//request_gravar_nota;
			//nota, arquivo, ind_nota return true
		savenote_2(nota, cl_auth);
	}
}

void add_new_file(account *usr){	//ret 1 se ok e 0 se erro.

	file *fl;
	int num_fl;
	char cf[5];
	int add=0, id;

/////////////////////////////////////////////////////////////////////////////////////
	CLIENT *cl_auth;
	if (!(cl_auth = clnt_create(SERVER, ADDITPROG, ACCOUNT_MANAGER,"tcp"))) { 
        	clnt_pcreateerror(SERVER); 
        	return ERR_NOT_CONNECTED; 
    	}
/////////////////////////////////////////////////////////////////////////////////////

	num_fl = reqnewfile_2(usr, cl_auth);

	printf("%s \t %s", fl->date, fl->hour);
	printf("Informe o Titulo: ");
	scanf(fl->title, "&s");
	printf("------------------------------------------------------------------------------------------\n");
	printf("Conteudo: \n");
	scanf(fl->conteudo_inicial, "%s");

	fl->tam_note = 0;
	fl->num_link = num_fl;

	while(1){
		printf("Deseja adicionar nova permissao de usuario (yes,no): ");
		scanf(cf, "%s");
		if (strcmp(cf, "yes")){
			printf("ID: ");
			scanf(id, "%d");
			fl->permissoes[add] = id;
		}
		else break;
	}

	id = createnewfile_2(fl, cl_auth);
}





main(int argc, char *argv[]) {
    CLIENT *cl, *cl_auth;
    int answer;
    int ret, newFile;
    account *user = (account *) malloc(sizeof(account));

   

/*	ret = auth();
	if (ret != 0){
		printf("ret: %d\n\r", ret);
		return ret;
	}*/
	newFile = criar_nota(1,user);

	
/*	record *rec = (record *) malloc(sizeof(record));
	account *user_account = (account *) malloc(sizeof(account));
	
    if (argc != 4) {
        printf("Usage: %s hostname <operando> <operando>\n", argv[0]); 
		printf("Onde:\n");
		printf("        <hostname> hostname ou endereco IP do servidor.\n");
		printf("        <operando> deve ser um número inteiro.\n");
        exit (1); /////////////////////////////////////////////////////////////////////////////////////
	CLIENT *cl_auth;
	if (!(cl_auth = clnt_create(SERVER, ADDITPROG, ACCOUNT_MANAGER,"tcp"))) { 
        	clnt_pcreateerror(SERVER); 
        	return ERR_NOT_CONNECTED; 
    	}
/////////////////////////////////////////////////////////////////////////////////////
	} 

//	if (!(cl = clnt_create(argv[1], ADDITPROG,ADDITVERS,"tcp"))) { 
//        clnt_pcreateerror(argv[1]); 
//        exit(1); 
//    }

	if (!(cl_auth = clnt_create(argv[1], ADDITPROG, ACCOUNT_MANAGER,"tcp"))) { 
        clnt_pcreateerror(argv[1]); 
        exit(1); 
    }
//	user_account->user = (char[30])argv[2];
//	user_account->password = (char[30])argv[3];

//	user_account->user = "teste";
//	user_account->password = "teste";

//	strcpy(user_account->user, "teste");
//	strcpy(user_account->password, "teste");

//	strcpy(user_account->user, "teste");
//	strcpy(user_account->password, "teste");

//  rec->first_num = atoi(argv[2]); 
//  rec->second_num= atoi(argv[3]); 
//  answer = *add_args_1(rec,cl); 
	answer = *authentication_2(user_account,cl_auth);
	printf("answer %d\n\r", answer);
    if (answer < 0) { 
        printf("error: could not produce meaningful results\n\r"); 
        exit(1); 
    } 
    if (answer >= 0) { 
        printf("OK\n\r"); 
    } 


	strcpy(user_account->user, "te");
	strcpy(user_account->password, "teste");
//  rec->first_num = atoi(argv[2]); 
//  rec->second_num= atoi(argv[3]); 
//  answer = *add_args_1(rec,cl); 
	answer = *authentication_2(user_account,cl_auth);
    if (answer < 0) { 
        printf("error: could not produce meaningful results"); 
        exit(1); 
    } 
    if (answer >= 0) { 
        printf("OK\n\r"); 
    } 
	clnt_destroy(cl_auth);
	*/
}

