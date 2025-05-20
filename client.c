#include <stdio.h>
#include "graphingFunc.c"
#include "csv.c"
#include "tabulating.c"
#include "total_invoice.c"
#include "invoice.c"
#include "node.h"

int main() {
    int values[10] = {20000, 30000, 40000, 70000, 10000, 30000, 60000, 25000, 22000, -1};

    struct node *head = read_csv();
    printList(head);
    // plot(values, 1);
    generate_total_invoice(head);
    generate_invoice(head, 10010);

    return 0;
}