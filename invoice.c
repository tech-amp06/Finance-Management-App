#include <stdio.h>
#include <stdlib.h>
#include "csv.c"

void generate_invoice(struct node *head) {
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

    printf("============== INVOICE ==============\n");
    printf("Total Transactions: %d\n", total_transactions);
    printf("Total Expense (Debits): ₹ %d\n", total_expense);
    printf("-------------------------------------\n");
    printf("%-10s %-25s %-30s %-10s %s\n", "Date", "Account", "Note", "Amount", "D/C");
    printf("-------------------------------------------------------------------------------\n");

    current = head;
    while (current) {
        printf("%-10s %-25.25s %-30.30s ₹%-8d %-6s\n",
               current->date_time,
               current->from_acc,
               current->note,
               current->amount,
               current->debt_credit == 1 ? "Debit" : "Credit");
        current = current->next;
    }

    printf("=====================================\n");
}

