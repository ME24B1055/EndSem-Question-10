#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_history 6
#define max_components 10
#define name_len 20

// Structure definitions
typedef struct queue_node {
    char partname[name_len];
    struct queue_node* next;
} queue_node;

typedef struct {
    queue_node *start, *end;
} queue;

typedef struct stack_node {
    char partname[name_len];
    struct stack_node* next;
} stack_node;

typedef struct sll_node {
    char partname[name_len];
    struct sll_node* next;
} sll_node;

typedef struct dll_node {
    char partname[name_len];
    struct dll_node *prev, *next;
} dll_node;

typedef struct cll_node {
    char partname[name_len];
    struct cll_node* next;
} cll_node;

// Global variables
char history_data[max_history][name_len];
int total_history = 0;
queue test_queue = {NULL, NULL};
stack_node* stress_pile = NULL;
sll_node* strained_parts = NULL;
dll_node* secured_parts = NULL;
cll_node* urgent_repairs = NULL;

// Utility function Clears the input buffer after scanf or fgets to avoid leftover newlines messing up thr input
void flush_input_buffer() {
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}

// Queue operations
void enqueue(queue* q, const char* part) {
    queue_node* brand_new = (queue_node*)malloc(sizeof(queue_node));
    strcpy(brand_new->partname, part);
    brand_new->next = NULL;
    if(q->end == NULL) 
    {
        q->start = q->end = brand_new;
    }
    
    q->end->next = brand_new;
    q->end = brand_new;
}

char* dequeue(queue* q) {
    if(q->start == NULL){
        return NULL;
    } 
    
    queue_node* temp = q->start;
    char* part_copy = (char*)malloc(name_len * sizeof(char));//allocating charecter of max name length bytes
    strcpy(part_copy, temp->partname);//copying the name of dequeued part into
    
    q->start = q->start->next;
    if(q->start == NULL)
         q->end = NULL;
    
    free(temp);
    return part_copy;
}

// Stack operations
void push(stack_node** top, const char* part) {
    stack_node* node = (stack_node*)malloc(sizeof(stack_node));
    strcpy(node->partname, part);
    node->next = *top;
    *top = node;
}

char* pop(stack_node** top) {
    if(*top == NULL) 
        return NULL;
    
    stack_node* temp = *top;
    char* part_copy = (char*)malloc(name_len * sizeof(char));
    strcpy(part_copy, temp->partname);
    
    *top = (*top)->next;
    free(temp);
    return part_copy;
}

// History operations
void record_to_history(const char* result) {
    if(total_history < max_history) {
        strcpy(history_data[total_history], result);
        total_history++;
    } 
    else
     {
        for(int i = 0; i < max_history - 1; i++) {
            strcpy(history_data[i], history_data[i+1]);
        }
        strcpy(history_data[max_history - 1], result);
    }
}

// Singly Linked List operations
void insert_sll(sll_node** head, const char* part) {
    sll_node* brand_new = (sll_node*)malloc(sizeof(sll_node));
    strcpy(brand_new->partname, part);
    brand_new->next = *head;
    *head = brand_new;
}

void delete_sll(sll_node** head, const char* part) {
    sll_node *curr = *head, *prev = NULL;
    
    while(curr != NULL && strcmp(curr->partname, part) != 0) {
        prev = curr;
        curr = curr->next;
    }
    
    if(curr == NULL) 
        return;
    
    if(prev == NULL) 
        *head = curr->next;

    else {
        prev->next = curr->next;
    }
    
    free(curr);
}

// Doubly Linked List operations
void insert_dll(dll_node** head, const char* part) {

    dll_node* new_guy = (dll_node*)malloc(sizeof(dll_node));
    strcpy(new_guy->partname, part);
    new_guy->prev = NULL;
    new_guy->next = *head;
    
    if(*head != NULL) {
        (*head)->prev = new_guy;
    }
    
    *head = new_guy;
}

// Circular Linked List operations
void insert_cll(cll_node** head, const char* part) {

    cll_node* new_node = (cll_node*)malloc(sizeof(cll_node));
    strcpy(new_node->partname, part);
    
    if(*head == NULL) 
    {
        new_node->next = new_node;
        *head = new_node;
    } 
    else {
        cll_node* last = *head;
        while(last->next != *head) {
            last = last->next;
        }
        last->next = new_node;
        new_node->next = *head;
    }
}

// Menu display functions
void show_main_menu() {
    printf("\nMain Menu:\n");
    printf("1. Load Tests\n");
    printf("2. Stress Checks\n");
    printf("3. Load History\n");
    printf("4. Maintenance Tracking\n");
    printf("5. Priority Repairs\n");
    printf("6. Exit\n\n");
}

void manage_load_tests() {
    char name[name_len];
    int number_of_parts;
    
    printf("\n--- Load Test Management ---\n");
    printf("How many components to test? (Max %d): ", max_components);
    scanf("%d", &number_of_parts);
    flush_input_buffer();
    
    if(number_of_parts <= 0 || number_of_parts > max_components) {
        printf("Invalid number of components.\n");
        return;
    }
    
    for(int i = 0; i < number_of_parts; i++) {
        printf("Enter component %d name: ", i+1);
        fgets(name, name_len, stdin);
        name[strcspn(name, "\n")] = '\0';
        
        enqueue(&test_queue, name);
    }
    
    printf("\n%d components added to load test queue.\n", number_of_parts);
}

void manage_stress_checks() {
    printf("\n--- Stress Check Management ---\n");
    
    if(test_queue.start == NULL) {
        printf("No components in load test queue.\n");
        return;
    }
    
    printf("Processing load tests for stress checks...\n");
    
    while(test_queue.start != NULL) {
        char* partname = dequeue(&test_queue);
        push(&stress_pile, partname);
        free(partname);
    }
    
    printf("Stress check order (most critical first):\n");
    int idx = 1;
    while(stress_pile != NULL) {
        char* partname = pop(&stress_pile);
        printf("%d. %s\n", idx++, partname);
        free(partname);
    }
}

void manage_history() {
    printf("\n--- Load History ---\n");
    
    if(total_history == 0) {
        printf("No history records available.\n");
    }
    else
    {
        printf("Last %d test results:\n", total_history);
        for(int i = 0; i < total_history; i++) {
            printf("%d. %s\n", i+1, history_data[i]);
        }
    }
    
    printf("\nEnter new test result (or 'q' to quit): ");
    char new_result[name_len];
    fgets(new_result, name_len, stdin);
    new_result[strcspn(new_result, "\n")] = '\0';
    
    if(strcmp(new_result, "q") != 0) {
        record_to_history(new_result);
        printf("Result added to history.\n");
    }
}

void manage_maintenance() {
    printf("\n--- Maintenance Tracking ---\n");
    
    printf("Stressed components:\n");
    sll_node* ptr = strained_parts;
    int count = 1;
    while(ptr != NULL) {
        printf("%d. %s\n", count++, ptr->partname);
        ptr = ptr->next;
    }
    
    printf("\nReinforced components:\n");
    dll_node* dptr = secured_parts;
    count = 1;
    while(dptr != NULL) {
        printf("%d. %s\n", count++, dptr->partname);
        dptr = dptr->next;
    }
    
    printf("\n1. Add stressed component\n");
    printf("2. Mark component as reinforced\n");
    printf("3. Back to main menu\n");
    printf("Enter choice: ");
    
    int user_choice;
    scanf("%d", &user_choice);
    flush_input_buffer();
    
    char name[name_len];
    switch(user_choice) {
        case 1:
            printf("Enter component name: ");
            fgets(name, name_len, stdin);
            name[strcspn(name, "\n")] = '\0';
            insert_sll(&strained_parts, name);
            printf("%s added to stressed components.\n", name);
            break;
        case 2:
            if(strained_parts == NULL) {
                printf("No stressed components available.\n");
                break;
            }
            printf("Enter component to reinforce: ");
            fgets(name, name_len, stdin);
            name[strcspn(name, "\n")] = '\0';
            
            sll_node* search = strained_parts;
            int located = 0;
            while(search != NULL) {
                if(strcmp(search->partname, name) == 0) {
                    located = 1;
                    break;
                }
                search = search->next;
            }
            
            if(located) {
                delete_sll(&strained_parts, name);
                insert_dll(&secured_parts, name);
                printf("%s moved to reinforced components.\n", name);
            } else {
                printf("Component not found in stressed list.\n");
            }
            break;
        case 3:
            return;
        default:
            printf("Invalid choice.\n");
    }
}

void manage_repairs() {
    printf("\n--- Priority Repairs ---\n");
    
    if(urgent_repairs == NULL) {
        printf("No components in repair list.\n");
    } else {
        printf("Components needing urgent repair:\n");
        cll_node* ptr = urgent_repairs;
        int number = 1;
        do {
            printf("%d. %s\n", number++, ptr->partname);
            ptr = ptr->next;
        } while(ptr != urgent_repairs);
    }
    
    printf("\n1. Add component for urgent repair\n");
    printf("2. Back to main menu\n");
    printf("Enter choice: ");
    
    int menu_choice;
    scanf("%d", &menu_choice);
    flush_input_buffer();
    
    char item[name_len];
    switch(menu_choice) {
        case 1:
            printf("Enter component name: ");
            fgets(item, name_len, stdin);
            item[strcspn(item, "\n")] = '\0';
            insert_cll(&urgent_repairs, item);
            printf("%s added to urgent repairs.\n", item);
            break;
        case 2:
            return;
        default:
            printf("Invalid choice.\n");
    }
}

// Main function
int main() {
    int menu_select;
    
    printf("=== Smart Bridge Load Monitor ===\n");
    
    while(1) {
        show_main_menu();
        printf("Enter your choice: ");
        scanf("%d", &menu_select);
        flush_input_buffer();
        
        switch(menu_select) {
            case 1:
                manage_load_tests();
                break;
            case 2:
                manage_stress_checks();
                break;
            case 3:
                manage_history();
                break;
            case 4:
                manage_maintenance();
                break;
            case 5:
                manage_repairs();
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

