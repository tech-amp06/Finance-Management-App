#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024
#define MAX_COLS 20
#define MAX_ROWS 100
#define MAX_FIELD_LEN 100

typedef struct {
    char fields[MAX_COLS][MAX_FIELD_LEN];
} Row;

int tabulate(char filename[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char line[MAX_LINE_LEN];
    Row rows[MAX_ROWS];
    int rowCount = 0, colCount = 0;

    // Read the header
    if (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",\n");
        while (token) {
            strcpy(rows[0].fields[colCount++], token);
            token = strtok(NULL, ",\n");
        }
        rowCount = 1;
    }

    // Read data rows
    while (fgets(line, sizeof(line), file) && rowCount < MAX_ROWS) {
        int col = 0;
        char *token = strtok(line, ",\n");
        while (token && col < colCount) {
            strcpy(rows[rowCount].fields[col], token);
            token = strtok(NULL, ",\n");
            col++;
        }
        rowCount++;
    }

    fclose(file);

    // Print table header
    printf("\n%-20.19s", rows[0].fields[0]);
    for (int i = 1; i < colCount; i++)
        printf("| %-20.19s", rows[0].fields[i]);
    printf("\n");

    // Print a separator
    for (int i = 0; i < colCount; i++)
        printf("----------------------");
    printf("\n");

    // Print table rows
    for (int i = 1; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            printf("%-20.19s", rows[i].fields[j]);
            if (j != colCount - 1) printf("| ");
        }
        printf("\n");
    }

    return 0;
}