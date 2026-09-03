#include <stdio.h>   
#include <stdlib.h>  
#include <string.h> 

// A single node in the list
typedef struct Node {
    char* data;
    struct Node* next;
    struct Node* prev;
} Node;

// The list
typedef struct {
    Node* head;
    Node* tail;
} List;

// Makes our own heap copy of a string
char* copy_string(const char* text) {
    char* copy = malloc(strlen(text) + 1);
    strcpy(copy, text);
    return copy;
}

// Creates an empty list
void list_init(List* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Adds a new string to the end of the list
void list_insert(List* list, const char* text) {
    Node* node = malloc(sizeof(Node));
    node->data = copy_string(text);
    node->next = NULL;
    node->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = node;
    } else {
        // List was empty
        list->head = node;
    }

    list->tail = node;
}

// Searches the list for a matching string. Returns the Node if found,
// or NULL if it isn't in the list
Node* list_find(List* list, const char* text) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, text) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Returns 1 if something was deleted, 0 if the string wasn't found
int list_delete(List* list, const char* text) {
    Node* node = list_find(list, text);
    if (node == NULL) {
        return 0;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next; // node was the head
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev; // node was the tail
    }

    free(node->data);
    free(node);
    return 1;
}

// Prints the list from head to tail for testing
void list_print(List* list) {
    Node* current = list->head;
    printf("[");
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

// Frees every remaining node and string in the list
void list_free(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

int main() {
    List list;
    list_init(&list);

    printf("Hello, world!\n\n");

    list_insert(&list, "apple");
    list_insert(&list, "banana");
    list_insert(&list, "cherry");
    printf("After inserting apple, banana, cherry:\n");
    list_print(&list);

    Node* found = list_find(&list, "banana");
    printf("\nSearching for 'banana': %s\n", found ? "found" : "not found");

    Node* missing = list_find(&list, "grape");
    printf("Searching for 'grape': %s\n", missing ? "found" : "not found");

    printf("\nDeleting 'banana'...\n");
    list_delete(&list, "banana");
    list_print(&list);

    list_free(&list);
    return 0;
}
