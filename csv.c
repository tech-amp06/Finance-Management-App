#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_FIELDS 5

struct node {
    char date_time[5];
    char from_acc[20];
    char note[20];
    int amount;
    int debt_credit;
    struct node *next;
};

void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

struct node* createNode(char **fields) {
    struct node *newNode = malloc(sizeof(struct node));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(1);
    }

    strncpy(newNode->date_time, fields[0], sizeof(newNode->date_time));
    strncpy(newNode->from_acc, fields[1], sizeof(newNode->from_acc));
    strncpy(newNode->note, fields[2], sizeof(newNode->note));
    newNode->amount = atoi(fields[3]);
    newNode->debt_credit = atoi(fields[4]);
    newNode->next = NULL;

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
    printf("Time       | From Acc             | Note                           | Amount     | D/C\n");
    printf("-------------------------------------------------------------------------------------\n");
    while (head) {
        printf("%-10.10s | %-20.20s | %-30.30s | %10d | %d\n",
               head->date_time, head->from_acc, head->note,
               head->amount, head->debt_credit);
        head = head->next;
    }
}

struct node *read_csv() {
    FILE *fp = fopen("expenses_final.csv", "r");
    if (!fp) {
        perror("File open failed");
        return NULL;
    }

    struct node *head = NULL, *tail = NULL;
    char line[MAX_LINE];
    int line_num = 0;

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

        struct node *newNode = createNode(fields);
        if (!head)
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);

    return head;
}
