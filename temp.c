#include<stdlib.h>
#include<stdio.h>
#define MAX_USERS 4
#define USER_FILE "users.txt"

typedef struct {
    char username[50];
    char password[50];
} User;

User users[MAX_USERS];
int userCount = 0;

// Load users from the file
void loadUsers() {
    FILE *fp = fopen(USER_FILE, "r");
    if (!fp) return;

    while (fscanf(fp, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
        userCount++;
    }
    fclose(fp);
}

// Save new user to the file
void saveUser(User newUser) {
    FILE *fp = fopen(USER_FILE, "a");
    fprintf(fp, "%s %s\n", newUser.username, newUser.password);
    fclose(fp);
}

// Register new user
int registerUser() {
    User newUser;
    printf("Register\nUsername: ");
    scanf("%s", newUser.username);
    printf("Password: ");
    scanf("%s", newUser.password);

    // Check for duplicate
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, newUser.username) == 0) {
            printf("Username already exists!\n");
            return -1;
        }
    }

    users[userCount++] = newUser;
    saveUser(newUser);
    printf("Registration successful!\n");
    return 0;
}

// Login existing user
int loginUser(char *loggedInUser) {
    char username[50], password[50];
    printf("Login\nUsername: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(loggedInUser, username);
            printf("Login successful! Welcome, %s.\n", username);
            return 0;
        }
    }

    printf("Invalid username or password.\n");
    return -1;
}
