#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void generate_invoice(struct node *head, int invoice_no) {
    int total_expense = 0;
    struct node *current = head;
    int itr = 10000;

    while (itr != invoice_no) {
        current = current->next;
        itr++;
    }
    total_expense = current->amount;

    float tax = total_expense * 0.0276f;
    int grand_total = total_expense + (int)tax;

    printf("\n\n========== TRANSACTION INVOICE ===========\n");
    printf("Invoice No.       : %d\n", invoice_no);
    printf("Issue Date        : 19-08-2024\n");
    printf("Transaction Date  : %s\n", current->date_time);
    printf("To                : ORGANIZATION NAME\n");
    printf("==========================================\n");
    printf("Total Expense (Debits) : Rs. %d\n", total_expense);
    printf("Tax (2.76%%)            : Rs. %.2f\n", tax);
    printf("Grand Total            : Rs. %d\n", grand_total);
    printf("==========================================\n");
    printf("Signed by: ORGANIZATION NAME\n");
    printf("==========================================\n\n");
}