/* add_svc.c server code for the example application */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "addit.h"

int *add_args_1_svc(record *rec, struct svc_req *clnt) {

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

