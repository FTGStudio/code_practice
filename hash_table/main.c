/*

There are different ways to resolve a collision. This tutorial will rely upon a method called Separate Chaining, 
which aims to create independent chains for all items that have the same hash index. The implementation in this 
tutorial will create these chains using linked lists. Whenever there is a collision, additional items that collide
on the same index are added to an overflow bucket list. Thus, you will not have to delete any existing records on 
the hash table. Due to linked lists having O(n) time complexity for insertion, searching, and deletion, in case of
a collision, you will have a worst-case access time of O(n) as well. The advantage of this method is that it is a
good choice if your hash table has a low capacity.

*/


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 50000 // Size of the hash table

// Define the hash table item data structure
typedef struct Ht_item{
    char *key;
    char *value;
} Ht_item;


// Define Linked List
typedef struct LinkedList{
    Ht_item* item;
    struct LinkedList* next;
} LinkedList;

// Define the hash table
typedef struct HashTable{
    Ht_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
} HashTable;


LinkedList** create_overflow_buckets(HashTable* table){
    // Create the overflow buckets; an array of LinkedLists.
    LinkedList** buckets = (LinkedList**) calloc(table->size, sizeof(LinkedList*));

    for(int i=0; i<table->size; i++)
        buckets[i] = NULL;
    
    return buckets;
}

void free_linkedlist(LinkedList* list){
    LinkedList* temp = list;

    while(list){
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

void free_overflow_buckets(HashTable* table){
    // Free all the overflow bucket lists.
    LinkedList** buckets = table->overflow_buckets;

    for(int i=0; i<table->size; i++){
        free_linkedlist(buckets[i]);
    }

    free(buckets);
}

LinkedList* allocate_list(){
    // Allocates memory for a LinkedList pointer
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}

LinkedList *linkedlist_insert(LinkedList* list, Ht_item* item){
    // Inserts the item onto the LinkedList.
    if(!list){
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }else if(list->next == NULL){
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;

    while(temp->next->next){
        temp = temp->next;
    }

    LinkedList *node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
}

Ht_item* linkedList_remove(LinkedList *list){
    // removes the head from the LinkedList
    // returns the item of the popped element
    if(!list)
        return NULL;

    if(!list->next)
        return NULL;
    
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

unsigned long hash_function(char *str){
    unsigned long i = 0;

    for(int j=0; str[j]; j++){
        i += str[j];
    }

    return i;
}

Ht_item* create_item(char *key, char* value){
    // creates a pointer to a new HashTable item
    Ht_item* item = (Ht_item*) malloc(sizeof(Ht_item));
    item->key = (char*) malloc(strlen(key)+1);
    item->value = (char*) malloc(strlen(value)+1);
    strcpy(item->key, key);
    strcpy(item->value, value);
    
    return item;
}

HashTable* create_table(int size){
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc(table->size, sizeof(Ht_item));

    for(int i=0; i<table->size; i++){
        table->items[i] = NULL;
    }
    
    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

void free_item(Ht_item* item){
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table){
    for(int i=0; i < table->size; i++){
        Ht_item* item = table->items[i];

        if (item != NULL)
            free_item(item);
    }

    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item){

    LinkedList* head = table->overflow_buckets[index];

    if(head == NULL){
        // creates the list.
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }else{
        // insert to the list.
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}

char* ht_search(HashTable* table, char* key){

    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    if(item != NULL){
        if(strcmp(item->key, key) == 0){
            return item->value;
        }

        if(head == NULL)
            return NULL;
        
        item = head->item;
        head = head->next;
    }

    return NULL;
}

void ht_delete(HashTable* table, char* key){
    // Deletes an item from the table
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];


    if(item == NULL){
        // does not exist 
        return;
    }else{
        if(head == NULL && strcmp(item->key, key) == 0){
            // Collision does not exist
            //Remove the item
            // set table index to NULL
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }else if(head != NULL){
            // collision chain exists
            if(strcmp(item->key, key) == 0){
                // Remove this item
                // Set the head of the list as the new item.
                free_item(item);
                LinkedList* node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = create_item(node->item->key, node->item->value);
                free_linkedlist(node);
                table->overflow_buckets[index] = head;
                return;
            }

            LinkedList* curr = head;
            LinkedList* prev = NULL;

            while(curr){
                if(strcmp(curr->item->key, key) == 0){
                    if(prev == NULL){
                        // first element of the chain
                        // remove the chain
                        free_linkedlist(head);
                        table->overflow_buckets[index] = NULL;
                        return;
                    }else{
                        // This is somehwere in the chain
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linkedlist(curr);
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }

                curr = curr->next;
                prev = curr;
            }
        }
    }
}

void print_search(HashTable* table, char* key){
    char* val;

    if((val = ht_search(table, key)) == NULL){
        printf("Key: %s does not exist\n", key);
    }else{
        printf("Key: %s, Value:%s \n", key, val);
    }
}

void print_table(HashTable *table)
{
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table -> size; i++)
    {
        if (table -> items[i])
        {
            printf("Index:%d, Key:%s, Value:%s\n", i, table -> items[i] -> key, table -> items[i] -> value);
        }
    }

    printf("-------------------\n\n");
}

void ht_insert(HashTable* table, char* key, char* value){
    
    // Creates the item
    Ht_item *item = create_item(key, value);

    // Computes the index
    int index = hash_function(key);

    Ht_item *current_item = table->items[index];

    if(current_item == NULL){
        // Key does not exist
        if(table->count == table->size){
            // HashTable is full
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }

        // Insert item
        table->items[index] = item;
        table->count++;
    }else{
        // Scenario 1: Update the value
        if(strcmp(current_item->key, key) == 0){
            strcpy(table->items[index]->value, value);
            return;
        }else{
            // Scenario 2: Handle the collision.
            handle_collision(table, index, item);
            return;
        }
    }
}

void print_overflow_bucket(HashTable* ht, int index){
    // LinkedList* tmp;
    Ht_item *tmp;
    LinkedList *t;
    // Check to see if a list exists at index
    if(ht->overflow_buckets[index]->item){
        tmp = ht->overflow_buckets[index]->item;
        printf("Key: %s, Value: %s\n", tmp->key, tmp->value);
        t = ht->overflow_buckets[index];
        tmp = t->item;
        while(t){
            tmp = t->item;
            printf("Key: %s, Value: %s\n", tmp->key, tmp->value);
            t = t->next;
        }
    }
}

int main(int argc, char **argv){

    HashTable *ht = create_table(CAPACITY);
    ht_insert(ht, "1", "First address");
    ht_insert(ht, (char *)"1", (char *)"First address");
    ht_insert(ht, (char *)"2", (char *)"Second address");
    ht_insert(ht, (char *)"Hel", (char *)"Third address");
    ht_insert(ht, (char *)"Cau", (char *)"Fourth address");
    ht_insert(ht, (char *)"Cau", (char *)"Fourth address");
    ht_insert(ht, (char *)"Cau", (char *)"Fourth address");
    print_overflow_bucket(ht, 281);
    print_search(ht, (char *)"1");
    print_search(ht, (char *)"2");
    print_search(ht, (char *)"3");
    print_search(ht, (char *)"Hel");
    print_search(ht, (char *)"Cau"); // Collision!
    print_table(ht);
    ht_delete(ht, (char *)"1");
    ht_delete(ht, (char *)"Cau");
    print_table(ht);
    free_table(ht);
    return 0;
}