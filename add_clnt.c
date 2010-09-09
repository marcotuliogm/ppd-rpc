/* addit.c client code for the example application */

#include <stdio.h>
#include <string.h>
#include <list>
#include <rpc/rpc.h>
#include "addit.h"

main(int argc, char *argv[]) {

    CLIENT *cl, *cl_auth;
    int answer;

    record *rec = (record *) malloc(sizeof(record));
	account *user_account = (account *) malloc(sizeof(account));
	
    if (argc != 4) {
        printf("Usage: %s hostname <operando> <operando>\n", argv[0]); 
		printf("Onde:\n");
		printf("        <hostname> hostname ou endereco IP do servidor.\n");
		printf("        <operando> deve ser um número inteiro.\n");
        exit (1); 
	} 

	if (!(cl = clnt_create(argv[1], ADDITPROG,ADDITVERS,"tcp"))) { 
        clnt_pcreateerror(argv[1]); 
        exit(1); 
    }

	if (!(cl_auth = clnt_create(argv[1], ADDITPROG,AUTENTICATION,"tcp"))) { 
        clnt_pcreateerror(argv[1]); 
        exit(1); 
    }
//	user_account->user = (char[30])argv[2];
//	user_account->password = (char[30])argv[3];

//	user_account->user = "teste";
//	user_account->password = "teste";

	strcpy(user_account->user, "teste");
	strcpy(user_account->password, "teste");

//  rec->first_num = atoi(argv[2]); 
//  rec->second_num= atoi(argv[3]); 
//  answer = *add_args_1(rec,cl); 
	answer = *autentication_2(user_account,cl_auth);
    if (answer <= 0) { 
        printf("error: could not produce meaningful results"); 
        exit(1); 
    } 

    printf("%s + %s = %d\n", argv[2], argv[3], answer); 



//  rec->first_num = atoi(argv[2]); 
//  rec->second_num= atoi(argv[3]); 
//  answer = *add_args_1(rec,cl); 
	answer = *autentication_2(user_account,cl_auth);
    if (answer <= 0) { 
        printf("error: could not produce meaningful results"); 
        exit(1); 
    } 

    printf("%s + %s = %d\n", argv[2], argv[3], answer); 
}

