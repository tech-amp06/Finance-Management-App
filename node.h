#ifndef NODE_H
#define NODE_H

struct node {
    char date_time[20];
    char from_acc[20];
    char note[20];
    int amount;
    int debt_credit;
    int invoice_no;
    struct node *next;
};

#endif