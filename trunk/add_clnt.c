/* addit.c client code for the example application */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "addit.h"

#define SERVER "127.0.0.1"

enum ERROR{
	ERR_NOT_CONNECTED = -1,
	ERR_NOT_AUTHENTICATED,
};

int auth(){
	int answer;
    CLIENT *cl_auth;
	account *user_account = (account *) malloc(sizeof(account));
	

	if (!(cl_auth = clnt_create(SERVER, ADDITPROG, ACCOUNT_MANAGER,"tcp"))) { 
        clnt_pcreateerror(SERVER); 
        return ERR_NOT_CONNECTED; 
    }
	printf("Login:\n\r");
	printf("User: ");
	scanf("%s", user_account->user);
	printf("Password: ");
	scanf("%s", user_account->password);

	answer = *authentication_2(user_account,cl_auth);
	printf("answer %d\n\r", answer);
    if (answer < 0) { 
        printf("User or passworrd wrong: try again\n\r"); 
        return ERR_NOT_AUTHENTICATED; 
    } 

	clnt_destroy(cl_auth);
	return 0;
}

main(int argc, char *argv[]) {
//    CLIENT *cl, *cl_auth;
//    int answer;
	int ret;
	ret = auth();
	printf("ret: %d\n\r", ret);

/*	record *rec = (record *) malloc(sizeof(record));
	account *user_account = (account *) malloc(sizeof(account));
	
    if (argc != 4) {
        printf("Usage: %s hostname <operando> <operando>\n", argv[0]); 
		printf("Onde:\n");
		printf("        <hostname> hostname ou endereco IP do servidor.\n");
		printf("        <operando> deve ser um número inteiro.\n");
        exit (1); 
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

