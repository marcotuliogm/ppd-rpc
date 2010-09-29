/* addit.c client code for the example application */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "addit.h"

#define SERVER "127.0.0.1"
#define MENU_STR_SIZE 30

enum ERROR{
	ERR_NOT_CONNECTED = -1,
	ERR_NOT_AUTHENTICATED = -2,
};

//struct MENU_ITENS{
//	char descricao[30];
//}
char Menu_item[10][MENU_STR_SIZE] = {
	"Teste 0",
	"Teste 1",
	"Teste 2",
	"Teste 3",
	"Teste 4",
	"Teste 5",
	"Teste 6",
	"Teste 7",
	"Teste 8",
	"Teste 9"
};

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
		scanf("%s", user_account->user);
		printf("Password: ");
		scanf("%s", user_account->password);

		answer = *authentication_2(user_account, cl_auth);
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

main(int argc, char *argv[]) {
//    CLIENT *cl, *cl_auth;
//    int answer;
	int i, option;
	int ret;

	ret = auth();
	if (ret != 0){
		printf("ret: %d\n\r", ret);
		return ret;
	}

	printf("sizeof %d \n\r", sizeof(Menu_item));

	for(i = 0; i < sizeof(Menu_item)/MENU_STR_SIZE; i++){
		printf("%d %s\n\r", i+1, Menu_item[i]);
	}

	printf("Escolha uma opcao: ");
	scanf("%d", &option);
	switch (option){
		case 1:
				break;
		case 2:
				break;
		case 3:
				break;
		case 4:
				break;
		case 5:
				break;
		case 6:
				break;
		case 7:
				break;
		case 8:
				break;
		case 9:
				break;
		case 10:
				break;
		default:
				break;
	}

/*	record *rec = (record *) malloc(sizeof(record));

    if (argc != 4) {
        printf("Usage: %s hostname <operando> <operando>\n", argv[0]); 
		printf("Onde:\n");
		printf("        <hostname> hostname ou endereco IP do servidor.\n");
		printf("        <operando> deve ser um número inteiro.\n");
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

