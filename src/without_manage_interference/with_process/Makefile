all: process_credit process_debit process_transfer bank_transactions

bank_transactions : fonctions.o main.o
	cc -o bank_transactions main.o fonctions.o

process_credit : fonctions.o process_credit.o
	cc -o process_credit process_credit.o fonctions.o

process_debit : fonctions.o process_debit.o
	cc -o process_debit process_debit.o fonctions.o

process_transfer : fonctions.o process_transfer.o
	cc -o process_transfer process_transfer.o fonctions.o

main.o : main.c entete.h fonctions.h
	cc -c main.c

fonctions.o : fonctions.c fonctions.h entete.h 
	cc -c fonctions.c

process_credit.o : process_credit.c entete.h fonctions.h
	cc -c process_credit.c

process_debit.o : process_debit.c entete.h fonctions.h
	cc -c process_debit.c

process_transfer.o : process_transfer.c entete.h fonctions.h
	cc -c process_transfer.c

clean :
	rm  process_credit process_debit process_transfer bank_transactions main.o fonctions.o process_credit.o process_debit.o process_transfer.o
