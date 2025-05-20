#include <stdio.h>
#include "graphingFunc.c"
#include "csv.c"
#include "tabulating.c"

int main() {
    int values[10] = {20000, 30000, 40000, 70000, 10000, 30000, 60000, 25000, 22000, -1};

    read_csv("expense_data_1.csv");
    plot(values, 1);
    tabulate("expense_data_1.csv");

    return 0;
}