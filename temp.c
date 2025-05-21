#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_FIELDS 6

#include "node.h"

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
    strncpy(newNode->to_acc, fields[2], sizeof(newNode->to_acc));
    newNode->to_acc[sizeof(newNode->to_acc) - 1] = '\0';
    strncpy(newNode->note, fields[3], sizeof(newNode->note));
    newNode->note[sizeof(newNode->note) - 1] = '\0';
    newNode->amount = atoi(fields[4]);
    newNode->debt_credit = strcmp(fields[5], "Expense") == 0 ? 1 : 0;
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
        printf("%-10.10s | %-20.20s | %-20.20s | %-30.30s | %10d | %d  | %d\n",
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
    }

    fclose(fp);
    return head;
}

void addTransaction(struct node **head_ref) {
    static char date[100], from_acc[100], to_acc[100], note[100], amount[20], type[20];
    char *fields[MAX_FIELDS];

    fields[0] = date;
    fields[1] = from_acc;
    fields[2] = to_acc;
    fields[3] = note;
    fields[4] = amount;
    fields[5] = type;

    printf("Enter date (YYYY-MM-DD): ");
    scanf(" %[^\n]", fields[0]);

    printf("From account: ");
    scanf(" %[^\n]", fields[1]);

    printf("To account: ");
    scanf(" %[^\n]", fields[2]);

    printf("Note: ");
    scanf(" %[^\n]", fields[3]);

    printf("Amount: ");
    scanf(" %[^\n]", fields[4]);

    printf("Type (Expense or Income): ");
    scanf(" %[^\n]", fields[5]);

    static int invoice_no = 99999;  // Replace with tracking mechanism if needed
    struct node *newNode = createNode(fields, invoice_no++);
    newNode->next = *head_ref;
    *head_ref = newNode;

    printf("Transaction added successfully.\n");
}