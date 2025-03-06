#include <stdio.h>
#include <string.h>

typedef struct Node {
    char character;        
    int count;             
    struct Node* next;     
} Node;

const int MAX_NODES = 128;
Node nodePool[MAX_NODES];
int nodePoolIndex = 0;

// quick search using array ASCII
Node* charNodes[128] = {NULL};  

Node* createNode(char ascii) {
    if (nodePoolIndex < MAX_NODES) {
        Node* newNode = &nodePool[nodePoolIndex++];
        newNode->character = ascii;
        newNode->count = 1;
        newNode->next = NULL;
        return newNode;
    }
    printf("Error: Out of memory for nodes\n");
    return NULL;
}

void processChar(char ascii, Node** firstNode) {
    unsigned char index = (unsigned char)ascii;  // Use as array index

    //if new char
    if (charNodes[index] == NULL) {
        // new character
        Node* newNode = createNode(ascii);
        if (newNode == NULL) return;  
        
        // create the first node
        if (*firstNode == NULL) {
            *firstNode = newNode; 
        } else {
            // find the last node
            Node* current = *firstNode;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        // store in our direct access array
        charNodes[index] = newNode;
    } else {
        // if char already exists, add the count
        charNodes[index]->count++;
    }
}

int main() {
    FILE* file = fopen("main.c", "r");  
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    Node* firstNode = NULL;  
    int ascii;
    
    while ((ascii = fgetc(file)) != EOF) {
        processChar((char)ascii, &firstNode);
    }
    
    fclose(file);
    
    // Print 
    Node* current = firstNode;
    while (current != NULL) {
        if ((current->character >= 32 && current->character <= 126) || 
            current->character == '\n' || current->character == '\t') {
            
            // newline and tab 
            if (current->character == '\n') {
                printf("\\n : %d\n", current->count);
            } else if (current->character == '\t') {
                printf("\\t : %d\n", current->count);
            } else {
                printf("%c : %d\n", current->character, current->count);
            }
        }
        current = current->next;
    }
    
    return 0;
}
