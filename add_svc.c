/* add_svc.c server code for the example application */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "addit.h"
#include <time.h>

enum ERROR{
	ERR_NOT_CONNECTED = -1,
	ERR_NOT_AUTHENTICATED = -2,
};

int init = 0; /* Control if struct accounts alread initializated */
int max_users = 0; /* Read user of file */
Accounts accounts;

file files[100];	//max file
int count_file = 0;

int *add_args_1_svc(record *rec, struct svc_req *clnt) {

    static int result;

    result = rec->first_num + rec->second_num;
	printf("Teste %d %d \n\r", rec->first_num, rec->second_num);
    return ((int *) &result);
}

int *notauso_1_svc(int *num_file,  struct svc_req *clnt)
{
	files[*num_file].tam_note++;
	files[*num_file].notes[files[*num_file].tam_note].estou_em_uso = 1;
	return ((int *) &files[*num_file].tam_note);
}

file *arqedit_1_svc(int *num_fl,  struct svc_req *clnt){
	return ((file *) &files[*num_fl]);
//	return files[num_fl];
}

int *savenote_1_svc(note *nota, struct svc_req *clnt){
	int tam = files[nota->num_link].tam_note;
	files[nota->num_link].notes[tam] = *nota;
	 return ((int *) &nota->num_link);	//criar logica de confimação, DEPOIS
}

int *reqnewfile_1_svc(account *user, struct svc_req *clnt){
	struct tm *jn;
	time_t th;

	th = time(NULL);
	jn = localtime(&th);

	count_file++;
    	strftime(files[count_file].hour, 100, "%T", jn);
    	strftime(files[count_file].date, 100, "%A, %D.", jn);

	return ((int *) &count_file);
}

int *createnewfile_1_svc(file *fl, struct svc_req *clnt){

	int wh = fl->num_link;
	files[wh] = *fl;
	return ((int *) &fl->num_link);	//criar logica de confimação, DEPOIS
}

struct Accounts * showusers_1_svc(int *not_used, struct svc_req *clnt){
	static Accounts ret;
	ret = accounts;
	printf("Return accounts\n\r");
//	return (&accounts);	//criar logica de confimação, DEPOIS
	return (&ret);
}

int *authentication_2_svc(account *user_account, struct svc_req *clnt){
	static int result;
	char line[80];

	init_users();
	result = auth(user_account);
	sprintf(line, "user %s password %s - ", user_account->login, user_account->password);
	if (result < 0) printf("%s not authenticated\n\r", line);
	else printf("%s authenticated\n\r", line);
	return ((int *) &result);
}

init_users(){
	if (init) return 0;
	FILE * pfile;
	char user[10];
	char password[10];
	int index = 0;
	accounts.max_users = 0;
	init++;
	printf("Init Users\n\r");
	pfile = fopen ("file.txt", "r") ;
	if (pfile == NULL) return -1;
	while (!feof(pfile)){// && (mem_ind <= memory.partition[partition].last_address)){
		fscanf (pfile, "%10s%10s", user, password);
		accounts.user[index].ind = index;
		strcpy(accounts.user[index].login, user);
		strcpy(accounts.user[index].password, password);
		printf("index %d user: %s, password: %s\n\r", index, accounts.user[index].login, accounts.user[index].password);
		index++;
	}
	accounts.max_users = index-1;
}

int auth(account *user_account){
	int i;
	for (i = 0; i < accounts.max_users; i++){
		printf("Comparando %s com %s", user_account->login, accounts.user[i].login);
		if (!strcmp(user_account->login, accounts.user[i].login)){
			if (!strcmp(user_account->password, accounts.user[i].password)){
				printf("Ok \n\r");
				return 0;
			}
		}
		printf("NOk\n\r");
	}
	return ERR_NOT_AUTHENTICATED;
}

