/* add_svc.c server code for the example application */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "addit.h"

int *add_args_1_svc(record *rec, struct svc_req *clnt) {

    static int result;

    result = rec->first_num + rec->second_num;
	printf("Teste %d %d \n\r", rec->first_num, rec->second_num);

    return ((int *) &result);
}

int *authentication_2_svc(account *user_account, struct svc_req *clnt){
	static int result;
	char line[80];
	sprintf(line, "user %s password %s", user_account->user, user_account->password);
	printf("%s\n\r", line);
	result = 0;
	return ((int *) &result);
}

