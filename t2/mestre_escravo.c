#include <stdio.h>
#include <mpi.h>

#define	ARRAYSIZE	1000
#define MASTER		0         /* taskid of first process */
#define FIM             -999

int main(int argc,char **argv)
{
 int	   ntasks,           /* total number of MPI tasks in partitiion */
           nworkers,         /* number of worker tasks */
	   nchunks,
	   taskid,	     /* task identifier */
	   rc,               /* return error code */
	   dest,             /* destination task id to send message */
	   pares,
           index;            /* index into the array */
 
 long int  i, j, chunksize;  /* loop variable */
 
 int       arraymsg = 1,     /* setting a message type */
   	   indexmsg = 2,     /* setting a message type */
	   source;           /* origin task id of message */

 int	   data[ARRAYSIZE],     /* the intial array */
           result[ARRAYSIZE];    /* for holding results of array operations */
 
 MPI_Status status;


 srand ( time(NULL) );


 rc = MPI_Init(&argc,&argv);
 rc|= MPI_Comm_size(MPI_COMM_WORLD,&ntasks);
 rc|= MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
 if (rc != MPI_SUCCESS)
    printf ("Error initializing MPI and obtaining task ID information\n");
 // else
 //    printf ("\nMPI task ID = %d\n", taskid);
 //printf("%d tasks, I am task %d\n", ntasks, taskid);
 nworkers = ntasks-1;
 chunksize = 0.05 * (ARRAYSIZE);
 nchunks = ARRAYSIZE / chunksize;

/**************************** master task ************************************/
 if (taskid == MASTER)
    { 
     printf("MASTER: number of workers = %d\n",nworkers);
     printf("MASTER: number of chunks  = %d\n", nchunks);
     fflush(stdout);

     for(i=0; i<ARRAYSIZE; i++) 
          data[i] = rand()%1000;
     index = 0;

     /* Send each worker task its portion of the array */
     for (dest=1; dest<= nworkers; dest++)
        { 
         printf("MASTER: Sending chunk %d to worker %d\n",dest,dest);
         fflush(stdout);
	 
         //MPI_Send(buffer,count,type,dest,tag,comm)
         MPI_Send(&index, 1, MPI_INT, dest, indexmsg, MPI_COMM_WORLD);
         MPI_Send(&data[index], chunksize, MPI_INT, dest, arraymsg, MPI_COMM_WORLD);
         index = index + chunksize; //divide o array enviando uma parte para cada um fazer a sua parte.
        }

     nchunks = nchunks - nworkers;
     
     // Now wait to receive back the results from each worker task and print 
     // a few sample values 
     while (nchunks > (0 - nworkers))
        {
	 MPI_Recv(&index, 1, MPI_INT, MPI_ANY_SOURCE, indexmsg, MPI_COMM_WORLD, &status);
         MPI_Recv(&result[index], chunksize, MPI_INT, MPI_ANY_SOURCE, arraymsg, MPI_COMM_WORLD, &status);
	 if (nchunks > 0)
	   {	 
	    printf("MASTER: Receiving from worker %d, remaining %d nchunks\n",status.MPI_SOURCE,nchunks);
	    fflush(stdout);
	   } 
         
	 if (nchunks > 0)
	   {
	    nchunks --;   
            printf("MASTER: Sending chunk %d to worker %d\n",-(nchunks - 20),status.MPI_SOURCE);
	    fflush(stdout);
	 
	    MPI_Send(&index, 1, MPI_INT, status.MPI_SOURCE, indexmsg, MPI_COMM_WORLD);	           
	    MPI_Send(&data[index], chunksize, MPI_INT, status.MPI_SOURCE, arraymsg, MPI_COMM_WORLD);
		
	    index = index + chunksize;
	    printf ("FALTAM %d FATIAS\n", nchunks);
	   } 
	 else nchunks --;
	}     

     //printf("MESTRE SAIU DO LACO\n");
     //fflush(stdout);
     
     for (dest=1; dest<= nworkers; dest++)
        {
         printf("MASTER: Sending to worker %d : END\n",dest);
	 fflush(stdout);
         index = FIM;
         MPI_Send(&index, 1, MPI_INT, dest, indexmsg, MPI_COMM_WORLD);
        } 
     
     
     pares = 0;
      
     for(i=0; i<ARRAYSIZE; i++)
       {
	if (result[i] == 1) 
	  {
           printf("[%3d] ", data[i]);
           pares++;
	   if(pares % 10 == 0) printf("\n");
	  }
        }
      printf("\n\nMASTER: Numero de pares = %d\n", pares);
      fflush(stdout);
      printf("MASTER: All Done! \n");
   }

/**************************** worker task ************************************/

 if (taskid > MASTER)
   {   
    // Receive my portion of array from the master task 
    //int cont = 0;
    source = MASTER;

    while (index != FIM)
      {	    
       //MPI_Recv(buffer,count,type,source,tag,comm,status) 
       MPI_Recv(&index, 1, MPI_INT, source, indexmsg, MPI_COMM_WORLD, &status);
       //printf("Index = %d\n",index);
       //fflush(stdout);
       if (index != FIM)
         {
	  MPI_Recv(&result[index], chunksize, MPI_INT, source, arraymsg, MPI_COMM_WORLD, &status);
      
          //cont ++; 
          //printf("Slave %d received chunk %d\n", taskid, cont);
          //fflush(stdout);
          // Do a simple value assignment to each of my array elements 
          for(i=index; i< index + chunksize; i++)
            {
             if((result[i] % 2) == 0) result[i] = 1;
             else result[i] = 0;
            }       

          // Send my results back to the master task 
          dest = MASTER;
          MPI_Send(&index, 1, MPI_INT, dest, indexmsg, MPI_COMM_WORLD);
          MPI_Send(&result[index], chunksize, MPI_INT, MASTER, arraymsg, MPI_COMM_WORLD);
         }
       } 
    printf ("WORKER %d: finalized\n",taskid);
    fflush(stdout);
   }
 MPI_Finalize();
}


