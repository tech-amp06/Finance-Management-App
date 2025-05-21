#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_FIELDS 6

#include "node.h"

int curr_invoice_no = 10000;

void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

struct node* createNode(char **fields, int invoice_no) {
    struct node *newNode = malloc(sizeof(struct node));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(1);
    }

    strncpy(newNode->date_time, fields[0], sizeof(newNode->date_time));
    newNode->date_time[sizeof(newNode->date_time) - 1] = '\0';
    strncpy(newNode->from_acc, fields[1], sizeof(newNode->from_acc));
    newNode->from_acc[sizeof(newNode->from_acc) - 1] = '\0';
    strncpy(newNode->to_acc, fields[5], sizeof(newNode->to_acc));
    newNode->to_acc[sizeof(newNode->to_acc) - 1] = '\0';
    strncpy(newNode->note, fields[2], sizeof(newNode->note));
    newNode->note[sizeof(newNode->note) - 1] = '\0';
    newNode->amount = atoi(fields[3]);
    newNode->debt_credit = strcmp(fields[4], "Expense") == 0 ? 1 : 0;
    newNode->next = NULL;
    newNode->invoice_no = invoice_no;

    return newNode;
}

int splitCSV(char *line, char *fields[], int max_fields) {
    int count = 0;
    char *token = strtok(line, ",");
    while (token && count < max_fields) {
        trim(token);
        fields[count++] = token;
        token = strtok(NULL, ",");
    }
    return count;
}

void printList(struct node *head) {
    printf("Transaction History:\n");
    printf("Time       | From Acc             | To Acc               | Note                           | Amount     | D/C | Invoice no.\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    while (head) {
        printf("%-10.10s | %-20.20s | %-20.20s | %-30.30s | %10d | %d   | %d\n",
               head->date_time, head->from_acc, head->to_acc, head->note,
               head->amount, head->debt_credit, head->invoice_no);
        head = head->next;
    }
}

struct node *read_csv() {
    FILE *fp = fopen("expenses_final_corrected_full.csv", "r");
    if (!fp) {
        perror("File open failed");
        return NULL;
    }

    struct node *head = NULL, *tail = NULL;
    char line[MAX_LINE];
    int line_num = 0;
    int invoice_no = 10000;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        if (line[0] == '\n' || line[0] == '\r') continue;

        line[strcspn(line, "\n")] = 0;

        char *fields[MAX_FIELDS];
        int num_fields = splitCSV(line, fields, MAX_FIELDS);

        if (num_fields < MAX_FIELDS) {
            printf("Skipping line %d: insufficient fields\n", line_num);
            continue;
        }

        struct node *newNode = createNode(fields, invoice_no);
        if (!head)
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        invoice_no++;
        curr_invoice_no = invoice_no;
    }

    fclose(fp);

    return head;
}

struct node *write_csv(struct node *head) {
    struct node *iterator = head;
    FILE *fp = fopen("expenses_final.csv", "w");

    while (iterator) {
        

        iterator = iterator->next;
    }
}

struct node *addTransaction(struct node *head) {
    char *fields[MAX_FIELDS];
    char temp[20];
    char temp_date[20], temp_from[50], temp_to[50], temp_note[100], temp_amount[10], temp_type[10];
    
    for (int i = 0; i < MAX_FIELDS; i++) {
        fields[i] = malloc(100);
    }

    printf("Enter date and time of transaction: ");
    fgets(temp_date, sizeof(temp_date), stdin);
    temp_date[strcspn(temp_date, "\n")] = '\0';
    strcpy(fields[0], temp_date);

    strcpy(fields[1], "CUB - online payment");
    
    printf("Enter receiver account: ");
    fgets(temp_to, sizeof(temp_to), stdin);
    temp_to[strcspn(temp_to, "\n")] = '\0';
    strcpy(fields[5], temp_to);

    printf("Enter amount: ");
    fgets(temp_amount, sizeof(temp_amount), stdin);
    temp_amount[strcspn(temp_amount, "\n")] = '\0';
    strcpy(fields[3], temp_amount);

    printf("Note: ");
    fgets(temp_note, sizeof(temp_note), stdin);
    temp_note[strcspn(temp_note, "\n")] = '\0';
    strcpy(fields[2], temp_note);

    printf("Expense(1) or Income(0)?\n");
    fgets(temp_type, sizeof(temp_type), stdin);
    temp_type[strcspn(temp_type, "\n")] = '\0';
    fields[4] = strcmp(temp_type, "1") == 0 ? "1" : "0";

    struct node *newNode = createNode(fields, curr_invoice_no++);

    newNode->next = head;
    head = newNode;

    for (int i = 0; i < MAX_FIELDS; i++) {
        free(fields[i]);
    }

    return head;
}