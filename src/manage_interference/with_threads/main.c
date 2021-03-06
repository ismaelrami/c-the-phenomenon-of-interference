#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h> /* permet de récupérer les codes d’erreur */
#include "fonctions.h"
#include <pthread.h>

int main(int argc, char** argv)
{
  pthread_t thread_debit, thread_credit, thread_transfer;
  int accounts_number = atoi(argv[1]);
  int operations_number = atoi(argv[2]);
  int transaction_amount = atoi(argv[3]);
  int account_choose, bank_balance_before_transactions, bank_balance_after_transactions, result, i;
  transactions_infos *transactions_infos_ = (transactions_infos*)malloc(sizeof(transactions_infos));

  transactions_infos_->transactions_number = operations_number;
  transactions_infos_->transactions_amount = transaction_amount;
  transactions_infos_->accounts_number = accounts_number;

  accounts = (account **) malloc(sizeof(account*)*accounts_number);
  for(i = 0; i < accounts_number; i++)
  {
    accounts[i] = (account*)malloc(sizeof(account));
  }

  init_bank_accounts(accounts, accounts_number);

  bank_balance_before_transactions= bank_balance(accounts, accounts_number);

  result = pthread_create(&thread_debit, NULL, debit_manager,(void*)transactions_infos_);
  if(result != 0)
  {
    perror("Erreur dans la création du thread débiteur :");
  }

  result = pthread_create(&thread_credit, NULL, credit_manager, (void*)transactions_infos_);
  if(result != 0)
  {
    perror("Erreur dans la création du thread créditeur :");
  }

  result = pthread_create(&thread_transfer, NULL, transfer_manager, (void*)transactions_infos_);
  if(result != 0)
  {
    perror("Erreur dans la création du thread de transfert  : ");
  }

  pthread_join(thread_debit, NULL);
  pthread_join(thread_credit, NULL);
  pthread_join(thread_transfer, NULL);

  bank_balance_after_transactions = bank_balance(accounts, accounts_number);
  if(bank_balance_after_transactions != bank_balance_before_transactions)
    printf("Il y a eu d'interférences \n");
  else
    printf("Il n'y a pas d'interférences \n");
}
