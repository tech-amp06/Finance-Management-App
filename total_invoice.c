#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void generate_total_invoice(struct node *head) {
    int total_transactions = 0;
    int total_expense = 0;
    struct node *current = head;

    while (current) {
        total_transactions++;
        if (current->debt_credit == 1) {
            total_expense += current->amount;
        }
        current = current->next;
    }

    float tax = total_expense * 0.0276f;
    int grand_total = total_expense + (int)tax;

    printf("\n\n========== TRANSACTION INVOICE ===========\n");
    printf("Issue Date  : 19-08-2024\n");
    printf("To          : ORGANIZATION NAME\n");
    printf("==========================================\n");
    printf("Total Transactions     : %d\n", total_transactions);
    printf("Total Expense (Debits) : Rs. %d\n", total_expense);
    printf("Tax (2.76%%)            : Rs. %.2f\n", tax);
    printf("Grand Total            : Rs. %d\n", grand_total);
    printf("==========================================\n");
    printf("Signed by: ORGANIZATION NAME\n");
    printf("==========================================\n");
}