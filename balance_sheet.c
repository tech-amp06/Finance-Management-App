#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

// Month labels
const char *months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void generate_balance_table(struct node *head) {
    int income[12] = {0};
    int expense[12] = {0};

    while (head) {
        // Get month from first 2 digits of date_time (assumed format MMDD)
        char monthStr[3];
        strncpy(monthStr, head->date_time, 2);
        monthStr[2] = '\0';

        int monthIndex = atoi(monthStr) - 1;
        if (monthIndex < 0 || monthIndex > 11) {
            printf("Invalid month in data: %s\n", head->date_time);
            head = head->next;
            continue;
        }

        if (head->debt_credit == 1) {
            expense[monthIndex] += head->amount;
        } else {
            income[monthIndex] += head->amount;
        }

        head = head->next;
    }

    // Print the balance table
    printf("\nMonthly Balance Summary:\n");
    printf("+-------------------------------------------------------+\n");
    printf("| Month | Income (Rs) | Expense (Rs) | Net Balance (Rs) |\n");
    printf("+-------------------------------------------------------+\n");

    for (int i = 0; i < 12; i++) {
        int net = income[i] - expense[i];
        printf("| %-5s | %11d | %12d | %16d |\n",
               months[i], income[i], expense[i], net);
    }

    printf("+-------------------------------------------------------+\n");
}