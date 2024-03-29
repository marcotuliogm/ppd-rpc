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
Files files;
//file files[100];	//max file
int count_file = 0;

int *add_args_1_svc(record *rec, struct svc_req *clnt) {

    static int result;

    result = rec->first_num + rec->second_num;
	printf("Teste %d %d \n\r", rec->first_num, rec->second_num);
    return ((int *) &result);
}

struct note * getnote_1_svc(intret *param, struct svc_req *clnt){
	static note ret;
	if (!files.doc[param->param1].notes[param->param2].estou_em_uso){
		ret = files.doc[param->param1].notes[param->param2];
		files.doc[param->param1].notes[param->param2].estou_em_uso = 1;
		printf("Return note\n\r");
		return (&ret);
	}
	ret = files.doc[param->param1].notes[param->param2];
	return (&ret);
}

struct file * arqedit_1_svc(int *num_fl,  struct svc_req *clnt){
	return (&files.doc[*num_fl]);
}

int *savenote_1_svc(note *nota, struct svc_req *clnt){
	files.doc[nota->num_file].notes[nota->num_note] = *nota;

	return ((int *) &nota->num_file);	//criar logica de confimação, DEPOIS
}


int *reqnewfile_1_svc(int *user, struct svc_req *clnt){
	static int file_index;
	char buff[80];
	struct tm *jn;
	time_t th;

	file_index = files.max_files;
	printf("User %d request new file\n\r", *user);
	th = time(NULL);
	jn = localtime(&th);

	files.doc[file_index].date_time.dia = jn->tm_mday;
	files.doc[file_index].date_time.ano = jn->tm_year;
	files.doc[file_index].date_time.mes = jn->tm_mon;	
	files.doc[file_index].date_time.hora = jn->tm_hour;
	files.doc[file_index].date_time.min = jn->tm_min;
	files.doc[file_index].date_time.sec = jn->tm_sec;

	files.max_files++;
	return ((int *) &file_index);
}

int *createnewfile_1_svc(file *fl, struct svc_req *clnt){

	int wh = fl->num_link;
	files.doc[wh] = *fl;
	return ((int *) &fl->num_link);	//criar logica de confimação, DEPOIS
}

struct Files *showdocspermission_1_svc(int *user, struct svc_req *clnt){
	int i, j;
	static Files ret;
	ret.max_files = 0;
	printf("Show user files %d\n\r", *user);
	for(i=0; i<files.max_files ;i++){
		for(j=0; j<files.doc[i].count_permission; j++){
			if(*user == files.doc[i].permissoes[j]){
				printf("%d %d - %s\n\r", *user, files.doc[i].permissoes[j], files.doc[i].title);
				ret.doc[ret.max_files] = files.doc[i];
				ret.doc[ret.max_files].num_link = i;
				ret.max_files++;
			}
		}
	}
	return (&ret);
}

struct Accounts * showusers_1_svc(int *not_used, struct svc_req *clnt){
	static Accounts ret;
	ret = accounts;
	printf("Return accounts\n\r");
//	return (&accounts);	//criar logica de confimação, DEPOIS
	return (&ret);
}

int *checkper_1_svc(intret *param, struct svc_req *clnt){
	static int per = 0 ;
	int i;
	printf("Documento %d, user %d\n\r", param->param1, param->param2);
	for(i = 0; i < files.doc[param->param1].count_permission; i++){
		printf ("Comparando user com %d\n\r", files.doc[param->param1].permissoes[i]);	
		if(param->param2 == files.doc[param->param1].permissoes[i]){
		per = 1;
		}
	}
	return ((int *) &per);
}

int *setpermission_1_svc(intret *param, struct svc_req *clnt){
	static int result;
	int ind = param->param1;
	printf ("set permission for user %d to file %d\n\r", param->param2, param->param1);
	files.doc[ind].permissoes[files.doc[ind].count_permission] = param->param2;
	files.doc[ind].count_permission++;
	result = 0;
	return ((int *) &result);
}

struct file * getdocument_1_svc(int *document, struct svc_req *clnt){
	static file ret;
	ret = files.doc[*document];
	printf("Return file\n\r");
//	return (&accounts);	//criar logica de confimação, DEPOIS
	return (&ret);
}

int * createnewnote_1_svc(int *document, struct svc_req *clnt){
	static int ret;
	ret = files.doc[*document].tam_note;
	files.doc[*document].notes[ret].estou_em_uso = 1;
	files.doc[*document].tam_note++;
	printf("Return new note\n\r");
	return ((int *) &ret);
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
		accounts.user[index].ind = 0; //variavel para troca de dados
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
				return i;
			}
		}
		printf("NOk\n\r");
	}
	return ERR_NOT_AUTHENTICATED;
}

