#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int read_csv(char filename[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE];

    // Read and print each line
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;

        // Split by comma
        char *token = strtok(line, ",");
        while (token != NULL) {
            printf("%-15s", token); // aligned output
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    fclose(fp);
    return 0;
}
