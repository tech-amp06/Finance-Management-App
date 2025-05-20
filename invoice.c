#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

typedef struct {
    char date[20];
    char category[30];
    char note[50];
    float amount;
} Expense;

int main() {
    FILE *file = fopen("expense_data_1.csv", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    Expense expenses[100];
    int count = 0;
    float total = 0.0;
    char line[MAX_LINE];

    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        fscanf(line, "%[^,],%[^,],%[^,],%f",
               expenses[count].date,
               expenses[count].category,
               expenses[count].note,
               &expenses[count].amount);

        total += expenses[count].amount;
        count++;
    }

    fclose(file);

    // Print invoice
    printf("============== INVOICE ==============\n");
    printf("Total Transactions: %d\n", count);
    printf("Total Expense: ₹ %.2f\n", total);
    printf("-------------------------------------\n");
    printf("%-12s %-12s %-15s %s\n", "Date", "Category", "Note", "Amount");
    printf("-------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-12s %-12s %-15s ₹ %.2f\n",
               expenses[i].date,
               expenses[i].category,
               expenses[i].note,
               expenses[i].amount);
    }

    printf("=====================================\n");

    return 0;
}