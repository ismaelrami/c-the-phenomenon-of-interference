#include "fonctions.h"
#include <stdlib.h>

int random_account_choose(int maximum, int choose)
{
  int i;
  i = rand()%(maximum-0) +0;
  while(i == choose)
  {
    i = rand()%(maximum-0) +0;
  }
  return i;
}

int random_account_amount(int minimum, int maximum)
{
  int balance;
  balance = rand()%(maximum-minimum) +minimum;
  return balance;
}

int bank_balance(account **accounts, int accounts_number)
{
  int bank_balance_ = 0,i;
  for(i = 0; i < accounts_number; i++)
  {
    bank_balance_ = bank_balance_ + accounts[i]->balance;
  }
  return bank_balance_;
}

void init_bank_accounts(account **accounts, int accounts_number)
{
  int i;
  for(i = 0; i < accounts_number; i++)
  {
    int balance_ = random_account_amount(100000, 1000000);
    accounts[i]->number = i + random_account_amount(1000000,2000000);
    accounts[i]->balance = balance_;
  }
}

void* credit_manager(void *data)
{
  int i;
  transactions_infos *transactions_infos_ = (transactions_infos*)malloc(sizeof(transactions_infos));
  transactions_infos_ = (transactions_infos*)data;
  for(i = 0; i < transactions_infos_->transactions_number; i++)
  {
    int account_choose_credit_number = random_account_choose(transactions_infos_->accounts_number, transactions_infos_->accounts_number+1);
    credit(account_choose_credit_number, transactions_infos_->transactions_amount);
  }
}

void credit(int account_number, int transaction_amount)
{
  account *account_for_credit = (account*)malloc(sizeof(account));
  account_for_credit = accounts[account_number];
  account_for_credit->balance = account_for_credit->balance + transaction_amount;

}


void* debit_manager(void *data)
{
  int i;
  transactions_infos *transactions_infos_ = (transactions_infos*)malloc(sizeof(transactions_infos));
  transactions_infos_ = (transactions_infos*)data;
  for(i = 0; i < transactions_infos_->transactions_number; i++)
  {
    int account_choose_debit_number = random_account_choose(transactions_infos_->accounts_number, transactions_infos_->accounts_number+1);
    debit(account_choose_debit_number, transactions_infos_->transactions_amount);
  }
}

void debit(int account_number, int transaction_amount)
{
  account *account_for_debit = (account*)malloc(sizeof(account));
  account_for_debit = accounts[account_number];
  account_for_debit->balance = account_for_debit->balance - transaction_amount;
}

void* transfer_manager(void *data)
{
  int i;
  transactions_infos *transactions_infos_ = (transactions_infos*)malloc(sizeof(transactions_infos));
  transactions_infos_ = (transactions_infos*)data;
  for(i = 0; i < transactions_infos_->transactions_number; i++)
  {
    int account_choose_transfer_source_number = random_account_choose(
                                                                      transactions_infos_->accounts_number,
                                                                      transactions_infos_->accounts_number+1
                                                                      );
    int account_choose_transfer_destination_number = random_account_choose(
                                                                            transactions_infos_->accounts_number,
                                                                            account_choose_transfer_source_number
                                                                            );
    transfer(
            account_choose_transfer_source_number,
            account_choose_transfer_destination_number,
            transactions_infos_->transactions_amount
            );
  }
}

void transfer(int source_account_number, int destination_account_number, int transaction_amount)
{
  debit(source_account_number, transaction_amount);
  credit(destination_account_number, transaction_amount);
}



