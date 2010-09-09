/* this code will be translated into the needed stubs and headers */
/* use: rpcgen addit.x; */

struct record {     /* arguments for RPC must be one single */
int first_num;      /* value or a structure of values */
int second_num;     /* first_num and second_num are addends */
}; 

struct account {
	int ind;
	char user[30];
	char password[30];
};


program ADDITPROG {                /* value to register the program */
    version ADDITVERS {            /* version must be assigned a value */
        int ADD_ARGS(record) = 1;  /* this is the service function */
    } =1;                          /* version value */
	version ACCOUNT_MANAGER {			/* Service for authentications*/
		int AUTENTICATION(account) = 1;
	} =2;
} = 0x20000003;                    /* program value */   
