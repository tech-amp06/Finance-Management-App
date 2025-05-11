#include <stdio.h>

int getMax(int values[], int length) {
    int maxExpense = values[0];

    for (int i = 1; i < length; i++) {
        if (maxExpense < values[i]) {
            maxExpense = values[i];
        }
    }

    return maxExpense;
}

int getMonthCount(int values[]) {
    int length;

    for (length = 0; values[length] != -1; length++);
    return length;
}

void plot(int values[], int firstMonth) {
    int monthCount = getMonthCount(values);
    int maxExpense = getMax(values, monthCount);
    int scale[2] = {maxExpense / 1000, monthCount * 2 + 1};
    char calendar[12][4] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

    printf("\nGRAPHICAL REPRESENTATION OF EXPENSES IN THE YEAR 2024\n");
    printf("-----------------------------------------------------\n\n");
    printf("    ^\n");

    for (int month = firstMonth; month < monthCount + firstMonth; month++) {
        printf("    | \n");
        printf("%s | ", calendar[month]);

        for (int value = 0; value < values[month - firstMonth] / 1000; value++) {
            printf("*");
        }
        printf("\n");
    }

    printf("    | \n------");
    
    for (int x = 0; x < scale[0]; x++) {
        printf("-");
    }
    printf(">\n");
    printf("    0 ");

    for (int multiplier = 1; multiplier <= scale[0] / 10; multiplier++) {
        printf("        %d", multiplier * 10);
    }
    printf("\n ");
}