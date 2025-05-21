#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

const char *monthList[] = {
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

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

int getAverage(int values[], int length) {
    int avg = 0;

    for (int i = 0; i < length; i++) {
        avg += values[i];
    }

    return avg / length;
}

void analyse(struct node *head) {
    int income[12] = {0};
    int expense[12] = {0};

    while (head) {
        // Get month from first 2 digits of date_time (assumed format MMDD)
        char monthListtr[3];
        strncpy(monthListtr, head->date_time, 2);
        monthListtr[2] = '\0';

        int monthIndex = atoi(monthListtr) - 1;
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

    printf("\nGRAPHICAL REPRESENTATION OF EXPENSES IN THE YEAR 2024\n");
    printf("-----------------------------------------------------\n\n");
    printf("    ^\n");

    for (int month = 0; month < 12; month++) {
        printf("    | \n");
        printf("%s | ", monthList[month]);

        for (int value = 0; value < income[month] / 500; value++) {
            if (income[month] > 0 && income[month] / 500 == 0) {
                printf("*");
            }
            printf("*");
        }
        if (month == getMax(income, 12)) {
            printf(" [PEAK: %d]", income[getMax(income, 12)]);
        }
        if (month == getMin(income, 12)) {
            printf(" [LEAST: %d]", income[getMin(income, 12)]);
        }
        printf("\n");
    }

    printf("    | \n------");
    
    for (int x = 0; x < income[getMax(income, 12)] / 500; x++) {
        printf("-");
    }
    printf(">\n");
    printf("    0 ");

    for (int multiplier = 1; multiplier <= income[getMax(income, 12)] / 2000 + 1; multiplier++) {
        printf("%4d", multiplier * 20);

    }
}