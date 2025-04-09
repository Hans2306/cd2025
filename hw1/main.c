#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 64

// Linked list node reused from HW0, now for tokens
typedef struct Node {
    char tokenStr[MAX_TOKEN_LEN];
    char tokenType[32];
    struct Node* next;
} Node;

const int MAX_NODES = 1024;
Node nodePool[MAX_NODES];
int nodePoolIndex = 0;
Node* firstNode = NULL;

Node* createNode(const char* str, const char* type) {
    if (nodePoolIndex < MAX_NODES) {
        Node* newNode = &nodePool[nodePoolIndex++];
        strncpy(newNode->tokenStr, str, MAX_TOKEN_LEN);
        strncpy(newNode->tokenType, type, 32);
        newNode->next = NULL;

        if (firstNode == NULL) {
            firstNode = newNode;
        } else {
            Node* current = firstNode;
            while (current->next != NULL) current = current->next;
            current->next = newNode;
        }
        return newNode;
    }
    return NULL;
}

void add_token(const char* str) {
    if (strcmp(str, "int") == 0) createNode(str, "TYPE_TOKEN");
    else if (strcmp(str, "main") == 0) createNode(str, "MAIN_TOKEN");
    else if (strcmp(str, "if") == 0) createNode(str, "IF_TOKEN");
    else if (strcmp(str, "else") == 0) createNode(str, "ELSE_TOKEN");
    else if (strcmp(str, "while") == 0) createNode(str, "WHILE_TOKEN");
    else if (isdigit(str[0])) createNode(str, "LITERAL_TOKEN");
    else createNode(str, "ID_TOKEN");
}

void scanner(FILE* file) {
    int c, next;
    char token[MAX_TOKEN_LEN];
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) continue;

        // ID or keyword
        if (isalpha(c) || c == '_') {
            int i = 0;
            token[i++] = c;
            while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_')) {
                token[i++] = c;
            }
            token[i] = '\0';
            add_token(token);
            if (c != EOF) ungetc(c, file);
        }

        // Integer literal
        else if (isdigit(c)) {
            int i = 0;
            token[i++] = c;
            while ((c = fgetc(file)) != EOF && isdigit(c)) {
                token[i++] = c;
            }
            token[i] = '\0';
            add_token(token);
            if (c != EOF) ungetc(c, file);
        }

        // Operators and symbols
        else {
            next = fgetc(file);
            switch (c) {
                case '=':
                    if (next == '=') createNode("==", "EQUAL_TOKEN");
                    else { createNode("=", "ASSIGN_TOKEN"); if (next != EOF) ungetc(next, file); }
                    break;
                case '>':
                    if (next == '=') createNode(">=", "GREATEREQUAL_TOKEN");
                    else { createNode(">", "GREATER_TOKEN"); if (next != EOF) ungetc(next, file); }
                    break;
                case '<':
                    if (next == '=') createNode("<=", "LESSEQUAL_TOKEN");
                    else { createNode("<", "LESS_TOKEN"); if (next != EOF) ungetc(next, file); }
                    break;
                case '+': createNode("+", "PLUS_TOKEN"); if (next != EOF) ungetc(next, file); break;
                case '-': createNode("-", "MINUS_TOKEN"); if (next != EOF) ungetc(next, file); break;
                case '(': createNode("(", "LEFTPAREN_TOKEN"); if (next != EOF) ungetc(next, file); break;
                case ')': createNode(")", "REFTPAREN_TOKEN"); if (next != EOF) ungetc(next, file); break;
                case '{': createNode("{", "LEFTBRACE_TOKEN"); if (next != EOF) ungetc(next, file); break;
                case '}': createNode("}", "REFTBRACE_TOKEN"); if (next != EOF) ungetc(next, file); break;
                case ';': createNode(";", "SEMICOLON_TOKEN"); if (next != EOF) ungetc(next, file); break;
                default:
                    token[0] = c;
                    token[1] = '\0';
                    createNode(token, "UNKNOWN_TOKEN");
                    if (next != EOF) ungetc(next, file);
                    break;
            }
        }
    }
}

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%99s", filename);

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    scanner(file);
    fclose(file);

    Node* current = firstNode;
    while (current != NULL) {
        printf("%s: %s\n", current->tokenStr, current->tokenType);
        current = current->next;
    }

    return 0;
}
