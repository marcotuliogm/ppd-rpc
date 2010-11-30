/*
blowfish_test.c:  Test file for blowfish.c

Copyright (C) 1997 by Paul Kocher

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <mpi.h>

#include "blowfish.c"
#define MAX_SIZE 1000000

#define MASTER 0         /* taskid of first process */
#define FIM -999

int main(int argc,char **argv)
{
	unsigned char key[] = "TESTKEY";
	unsigned long L = 0, R = 0;
	char vet[MAX_SIZE];
	unsigned long result[MAX_SIZE/4];
	int size;
	FILE * pFile;
	int c;//, i=0, j=0;
	int n = 0;
	BLOWFISH_CTX ctx;

/* MPI variables */
	
	int	ntasks,           /* total number of MPI tasks in partitiion */
		nworkers,         /* number of worker tasks */
		nchunks,
		taskid,	     /* task identifier */
		rc,               /* return error code */
		dest,             /* destination task id to send message */
		pares,
		index = 0,            /* index into the array */
		ret_index = 0;
	long int  i, j, chunksize, chunkretsize;  /* loop variable */
 	int arraymsg = 1,     /* setting a message type */
		indexmsg = 2,     /* setting a message type */
		source;           /* origin task id of message */
	 MPI_Status status;

	/* MPI init */
	rc = MPI_Init(&argc,&argv);
	rc|= MPI_Comm_size(MPI_COMM_WORLD,&ntasks);
	rc|= MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
	if (rc != MPI_SUCCESS)
	   printf ("Error initializing MPI and obtaining task ID information\n");
	// else
	//    printf ("\nMPI task ID = %d\n", taskid);
	//printf("%d tasks, I am task %d\n", ntasks, taskid);
	nworkers = ntasks-1;
	chunksize = 8;
	chunkretsize = 2;

	
	/* Blowfish init in all workers*/

	Blowfish_Init (&ctx, key, sizeof(key)-1);

	/* Master - read the file split and send to workers, write result*/

	if (taskid == MASTER){
		/*Open and read file*/
		pFile = fopen ("text.txt", "r");
		if (pFile == NULL)
			perror ("Error opening file");
		else {
			do {
				vet[i] = fgetc (pFile);
				i++;
			} while (vet[i-1] != EOF);
			size = i-2;
			fclose (pFile);
//			printf ("The file contains %d characters.\n", size);
		}
//		printf("%08lX %08lX\n", vet[0], vet[4]);

		/* adjust size */
		if (size%8){
//			printf("Não é exata %d\n\r", size%8);
			for (i = size; i < size+(8-size%8); i++){
				vet[i] = ' ';
			}
			size = i;
			printf ("The file contains %d characters.\n", size);
		}
		nchunks = size / chunksize;
		printf("MASTER: number of workers = %d\n",nworkers);
		printf("MASTER: number of chunks  = %d\n", nchunks);
		fflush(stdout);

     /* Send each worker task its portion of the array */
	 	for (dest = 1; dest <= nworkers; dest++) {
//	         printf("MASTER: Sending chunk %d to worker %d\n",dest,dest);
//	         fflush(stdout);

	         //MPI_Send(buffer,count,type,dest,tag,comm)
	         MPI_Send(&index, 1, MPI_INT, dest, indexmsg, MPI_COMM_WORLD);
	         MPI_Send(&vet[index], chunksize, MPI_INT, dest, arraymsg, MPI_COMM_WORLD);
	         index = index + chunksize; //divide o array enviando uma parte para cada um fazer a sua parte.
		}

		nchunks = nchunks - nworkers;
	    // Now wait to receive back the results from each worker task and print
	    // a few sample values

		while (nchunks > (0 - nworkers)) {
			MPI_Recv(&ret_index, 1, MPI_INT, MPI_ANY_SOURCE, indexmsg, MPI_COMM_WORLD, &status);
	        MPI_Recv(&result[ret_index/4], chunksize, MPI_INT, MPI_ANY_SOURCE, arraymsg, MPI_COMM_WORLD, &status);
		 	if (nchunks > 0) {
//				printf("work %d index %d ret_index %d - %08lX %08lX\n", status.MPI_SOURCE, ret_index, index, result[index/4], result[(index/4)+1]);
//			    printf("MASTER: Receiving from worker %d, remaining %d nchunks\n",status.MPI_SOURCE,nchunks);
//			    fflush(stdout);
			}
			if (nchunks > 0) {
		    	nchunks --;
//	            printf("MASTER: Sending chunk	 %d to worker %d\n",-(nchunks - 20),status.MPI_SOURCE);
//		    	fflush(stdout);
			    MPI_Send(&index, 1, MPI_INT, status.MPI_SOURCE, indexmsg, MPI_COMM_WORLD);	           
			    MPI_Send(&vet[index], chunksize, MPI_INT, status.MPI_SOURCE, arraymsg, MPI_COMM_WORLD);
			    index = index + chunksize;
//			    printf ("FALTAM %d FATIAS\n", nchunks);
		   	}
		 	else nchunks --;
		}

	     //printf("MESTRE SAIU DO LACO\n");
	     //fflush(stdout);
		for (dest=1; dest<= nworkers; dest++) {
//			printf("MASTER: Sending to worker %d : END\n",dest);
//			fflush(stdout);
			index = FIM;
			MPI_Send(&index, 1, MPI_INT, dest, indexmsg, MPI_COMM_WORLD);
		}

		/* Write output file*/
		pFile=fopen ("encoded_text.txt","w");
		for (i=0; i<size/4; i++){
			fprintf(pFile, "%08lx", result[i]);
		}
		pclose(pFile);



	}


/**************************** worker task ************************************/

if (taskid > MASTER) {
    // Receive my portion of array from the master task 
    //int cont = 0;
	char data[chunksize];
	unsigned long return_data[2];
    source = MASTER;

    while (index != FIM)
      {	    
       //MPI_Recv(buffer,count,type,source,tag,comm,status) 
       MPI_Recv(&index, 1, MPI_INT, source, indexmsg, MPI_COMM_WORLD, &status);
       //printf("Index = %d\n",index);
       //fflush(stdout);
       if (index != FIM)
	   {

		MPI_Recv(&data[0], chunksize, MPI_INT, source, arraymsg, MPI_COMM_WORLD, &status);
//		printf("worker %d index %d encoding %8c\n\r", taskid, index, data);
		fflush(stdout);
	  	L = data[0]<<24 | data[1]<<16 | data[2]<<8 | data[3];
		R = data[4]<<24 | data[5]<<16 | data[6]<<8 | data[7];

		Blowfish_Encrypt(&ctx, &L, &R);

		return_data[0] = L;
		return_data[1] = R;
			
		// Send my results back to the master task 
		dest = MASTER;
		MPI_Send(&index, 1, MPI_INT, dest, indexmsg, MPI_COMM_WORLD);
		MPI_Send(&return_data[0], chunkretsize, MPI_INT, MASTER, arraymsg, MPI_COMM_WORLD);
		}
	} 
//    printf ("WORKER %d: finalized\n",taskid);
//    fflush(stdout);
   }

	/* Write encoded file	*/
	pFile=fopen ("encoded_text.txt","w");
	for (i=0; i<size/4; i++){
		fprintf(pFile, "%08lx", result[i]);
	}
	pclose(pFile);
 	MPI_Finalize();
}

