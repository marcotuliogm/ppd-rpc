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
#include "blowfish.c"
#define MAX_SIZE 1000000

void main(void)
{
	unsigned char key[] = "TESTKEY";
	unsigned long L = 1, R = 2;
	char vet[MAX_SIZE];
	unsigned long result[MAX_SIZE/4];
	int size;
	FILE * pFile;
	int c, i=0, j=0;
	int n = 0;
	BLOWFISH_CTX ctx;
	Blowfish_Init (&ctx, key, sizeof(key)-1);
	printf("unsigned long %d\r\n", sizeof(unsigned long));
	printf("char %d\r\n", sizeof(char));

	/*Open and read file*/
	pFile=fopen ("text.txt","r");
	if (pFile==NULL)
		perror ("Error opening file");
	else
	{
		do {
			vet[i] = fgetc (pFile);
			i++;
		} while (vet[i-1] != EOF);
		size = i-2;
		fclose (pFile);
		printf ("The file contains %d characters.\n", size);
	}
//	printf("%08lX %08lX\n", vet[0], vet[4]);
	/* adjust size */	
	if (size%8){
		printf("Não é exata %d\n\r", size%8);
		for (i = size; i < size+(8-size%8); i++){
			vet[i] = ' ';
		}
		size = i;
		printf ("The file contains %d characters.\n", size);
	}

	/* Convert and encoding */
	for (i = 0; i<size; i=i+8){
		L = vet[i]<<24 | vet[i+1]<<16 | vet[i+2]<<8 | vet[i+3];
		R = vet[i+4]<<24 + vet[i+5]<<16 + vet[i+6]<<8 + vet[i+7];
		Blowfish_Encrypt(&ctx, &L, &R);
		result[j]=L;
		result[j+1]=R;
		j=j+2;
		//printf("%3d - %08lX , %08lX \n", i, L, R);
	}

	/* Write encoded file	*/
	pFile=fopen ("encoded_text.txt","w");
	for (i=0; i<size/4; i++){
		fprintf(pFile, "%08lx", result[i]);
	}
	pclose(pFile);

//	printf("%08lX %08lX\n", L, R);
//	Blowfish_Encrypt(&ctx, &L, &R);
//	printf("%08lX %08lX\n", L, R);
//	if (L == 0xDF333FD2L && R == 0x30A71BB4L)
//		printf("Test encryption OK.\n");
//	else
//		printf("Test encryption failed.\n");


//	Blowfish_Decrypt(&ctx, &L, &R);
//	if (L == 1 && R == 2)
//		printf("Test decryption OK.\n");
//	else
//		printf("Test decryption failed.\n");
//	printf("%08lX %08lX\n", L, R);
}

