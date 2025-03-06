#include <stdio.h>
#include <string.h>

typedef struct Node {
    char character;       
    int count;             
    struct Node* next;     
} Node;

//using ASCII as memory because cannot use stdlib (malloc)
const int MAX_NODES = 256;
Node total_node[MAX_NODES];
int total_node_index = 0;

Node* createNode(char c) {
    if (total_node_index < MAX_NODES) {
        Node* new_node = &total_node[total_node_index++];
        new_node->character = c;
        new_node->count = 1;
        new_node->next = NULL;
        return new_node;
    }
    printf("Error: Out of memory for nodes\n");
    return NULL;
}

Node* findOrAdd(Node* head, char c) {
    // if the list is empty, create the first node
    if (head == NULL) {
        return createNode(c);
    }
    
    // Check if the char is in the list
    Node* current = head;
    Node* prev = NULL;
    
    while (current != NULL) {
        if (current->character == c) {
            // if char found, plus count
            current->count++;
            return head;
        }
        prev = current;
        current = current->next;
    }
    
    // if char not found, add a new node
    Node* new_node = createNode(c);
    if (new_node != NULL) {
        // add to the end of the list
        prev->next = new_node;
    }
    
    return head;
}

int main() {
    FILE* file = fopen("main.c", "r");  
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    
    Node* head = NULL;  
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        head = findOrAdd(head, (char)c);
    }
    
    fclose(file);
    
    // print char counts
    Node* current = head;
    while (current != NULL) {

        if ((current->character >= 32 && current->character <= 126) || 
            current->character == '\n' || current->character == '\t') {
            
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
