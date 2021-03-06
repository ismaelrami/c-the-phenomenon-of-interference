#include "structures.h"

int random_account_choose(int, int);
int random_account_amount(int, int);
int bank_balance(account**, int);
void init_bank_accounts(account**, int);
void credit(int, int);
void debit(int, int);
void transfer(int, int, int);
void* credit_manager(void*);
void* debit_manager(void*);
void* transfer_manager(void*);
