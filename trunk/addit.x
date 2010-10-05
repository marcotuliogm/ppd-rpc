/* this code will be translated into the needed stubs and headers */
/* use: rpcgen addit.x; */

struct record {     /* arguments for RPC must be one single */
int first_num;      /* value or a structure of values */
int second_num;     /* first_num and second_num are addends */
};

struct intret {
	int param1;
	int param2;
};

#define MAX_NR 1000

typedef char text_t[30];
typedef char data_t[3000];
typedef int	vet[MAX_NR];

struct account{
	int ind;
	char login[30];
	char password[30];
};

struct Accounts{
	account user[30];
	int max_users;
};

struct note{
	text_t	title;
	text_t	user_edit;
	data_t conteudo;
	int num_link;
	int estou_em_uso;
};


struct file{
	text_t	title;
	text_t	date;
	text_t	hour;
	note notes[100];
	int tam_note;
	int permissoes[100];
	int count_permission;
	data_t conteudo_inicial;
	int num_link;
};

struct Files{
	file doc[100];
	int max_files;
};

program DOCS {                /* value to register the program */
    version DOCUMENTS_MANAGER {            /* version must be assigned a value */
        int ADD_ARGS(record) = 1;  /* this is the service function */
		int NOTAUSO(int) = 2;
		file ARQEDIT(int) = 3;
		int SAVENOTE(note) = 4;
		int REQNEWFILE(int) = 5;
		int CREATENEWFILE(file) = 6;
		Accounts SHOWUSERS(int) = 7;
		Files SHOWDOCSPERMISSION(int) = 8;
		int CHECKPER(intret) = 9;
		int SETPERMISSION(intret) = 10;
    } = 1;                          /* version value */
	version ACCOUNT_MANAGER {			/* Service for authentications*/
		int AUTHENTICATION(account) = 1;
	} = 2;
} = 0x20000003;                    /* program value */

