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
account accounts[30];

file files[100];	//max file
int count_file = 0;


int *add_args_1_svc(record *rec, struct svc_req *clnt) {

    static int result;

    result = rec->first_num + rec->second_num;
	printf("Teste %d %d \n\r", rec->first_num, rec->second_num);

    return ((int *) &result);
}

int *authentication_2_svc(account *user_account, struct svc_req *clnt){
	static int result;
	char line[80];

	init_users();
	result = auth(user_account);
	sprintf(line, "user %s password %s - ", user_account->user, user_account->password);
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
	init++;
	printf("Init Users\n\r");
	pfile = fopen ("file.txt", "r") ;
	if (pfile == NULL) return -1;
	while (!feof(pfile)){// && (mem_ind <= memory.partition[partition].last_address)){
		fscanf (pfile, "%10s%10s", user, password);
		accounts[index].ind = index;
		strcpy(accounts[index].user, user);
		strcpy(accounts[index].password, password);
		printf("index %d user: %s, password: %s\n\r", index, accounts[index].user, accounts[index].password);
		index++;
	}
	max_users = index;
}

int auth(account *user_account){
	int i;
	for (i=0;i<max_users;i++){
		printf("Comparando %s com %s", user_account->user, accounts[i].user);
		if (!strcmp(user_account->user, accounts[i].user)){
			if (!strcmp(user_account->password, accounts[i].password)){
				printf("Ok \n\r");
				return 0;
			}
		}
		printf("NOk\n\r");
	}
	return ERR_NOT_AUTHENTICATED;
}

int *nota_uso_2_svc(int *num_file,  struct svc_req *clnt)
{
	files[num_file].tam_notas++;
	files[num_file].notes[files[num_file].tam_notas].em_uso = 1;
	return ((int *) &files[num_file].tam_note);
}

file *arq_edit_2_svc(int *num_fl,  struct svc_req *clnt){
	return ((file*) &files[num_fl]);
}

int *save_note_2_svc(note *nota, struct svc_req *clnt){
	int tam = files[num_file].tam_notas; 
	files[nota->num_link].notes[tam] = &nota;
	 return ((int *) &tam);	//criar logica de confimação, DEPOIS
}


int *req_new_file_2_svc(account user, struct svc_req *clnt){

	struct tm *jn;
	time_t th;

	th = time(NULL);
	jn = localtime(&th);

	count_new_file++;
    	strftime(files[count_new_file]->hour, 100, "%T", ptr);
    	strftime(files[count_new_file]->date, 100, "%A, %D.", ptr);

	return ((int *) &count_new_file;	
}

int *creat_new_file_2_svc(file *fl, struct svc_req *clnt){
	
	int wh = fl->num_link;
	files[fl->wh] = &fl;
	return ((int *) &wh);	//criar logica de confimação, DEPOIS	
}




