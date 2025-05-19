#include <stdio.h>

int getMax(int values[], int length) {
    int monthOfMaxExpense = 0;

    for (int i = 1; i < length; i++) {
        if (values[monthOfMaxExpense] < values[i]) {
            monthOfMaxExpense = i;
        }
    }

    return monthOfMaxExpense;
}

int getMin(int values[], int length) {
    int monthOfMinExpense = 0;

    for (int i = 1; i < length; i++) {
        if (values[monthOfMinExpense] > values[i]) {
            monthOfMinExpense = i;
        }
    }

    return monthOfMinExpense;
}

int getMonthCount(int values[]) {
    int length;

    for (length = 0; values[length] != -1; length++);
    return length;
}

int getAverage(int values[], int length) {
    int avg = 0;

    for (int i = 0; i < length; i++) {
        avg += values[i];
    }

    return avg / length;
}

void plot(int values[], int firstMonth) {
    int monthCount = getMonthCount(values);
    int monthOfMaxExpense = getMax(values, monthCount);
    int monthOfMinExpense = getMin(values, monthCount);
    int averageExpense = getAverage(values, monthCount);
    int scale[2] = {values[monthOfMaxExpense] / 1000, monthCount * 2 + 1};
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

        if (month == monthOfMaxExpense + firstMonth) {
            printf(" [PEAK: %d]", values[monthOfMaxExpense]);
        }
        if (month == monthOfMinExpense + firstMonth) {
            printf(" [LEAST: %d]", values[monthOfMinExpense]);
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
    printf("\n     ");
}