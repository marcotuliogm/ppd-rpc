###############################################
#                                             #
# Makefile simples para compilar o programa   #
# ADDIT, exemplo de um servidor simples de    #
# rpc. Nesta funcao remota o processo         #
# sao passados como parametro dois numeros    #
# inteioros retornando a soma entre eles      #
#                                             #
#                                             #
###############################################

RM=rm -f
CC=gcc
LIBS=


all: generate_stubs client server 

client: 
	$(CC) add_clnt.c addit_clnt.o addit_xdr.o -o client 

server: 
	$(CC) add_svc.c addit_svc.o addit_xdr.o -o server 


generate_stubs: 
	rpcgen addit.x
	$(CC) -c addit_clnt.c
	$(CC) -c addit_svc.c	
	$(CC) -c addit_xdr.c	

clean:
	$(RM) addit_clnt.*
	$(RM) addit_svc.*
	$(RM) addit_xdr.*
	$(RM) addit.h
	$(RM) client
	$(RM) server
	$(RM) -fr *~




