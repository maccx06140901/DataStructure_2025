#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    char character;
    //int index;
    struct node* next;
    struct node* prev;
} node;

node* dummy;
node* first = NULL;
node* tail  = NULL;
node* cursor = NULL;//cursor:游標，插入的東西會是cursor指向的node的下一個

node* CreateNode(char character){
    node* ptr = malloc(sizeof(node));
    ptr->character = character, ptr->prev = NULL, ptr->next = NULL;
    return ptr;
}

void AddToList(node* newNode){
    if(first == NULL){
        first = newNode;
        tail = newNode;
        dummy->next = first;
        first->prev = dummy;
    }
    else{
        tail->next = newNode;
        newNode->prev = tail;
        tail = tail->next;
    }
    //printf("first: %c %d\n", newNode->character, newNode->index);
    return;
}

void InsertToList(node* newNode){
    newNode->prev = cursor;
    newNode->next = cursor->next;

    if(cursor->next != NULL){
        cursor->next->prev = newNode;
    } else {
        tail = newNode;
    }
    cursor->next = newNode;
    cursor = newNode;
    return;
}

void DeleteFromList(){
    if(cursor == dummy) return;
    node* toDelete = cursor;
    cursor->prev->next = cursor->next;
    if(cursor->next != NULL) cursor->next->prev = cursor->prev;
    else tail = cursor->prev;
    cursor = cursor->prev;
    free(toDelete);
    return;
}

void CursorMoveLeft(){
    if(cursor == dummy) return;
    cursor = cursor->prev;
    return;
}

void CursorMoveRight(){
    if(cursor->next == NULL) return;
    cursor = cursor->next;
    return;
}

void PrintList(){
    node* current = dummy->next;
    while(current != NULL){
        printf("%c", current->character);
        current = current->next;
    }
    return;
}

int main(){
    dummy = CreateNode('*');
    dummy->next = NULL;

    int N = -1;
    char message[300];
    //printf("testtest\n\n");
    scanf("%s", message);
    scanf("%d", &N);
    int i = 0;
    while(message[i] != '\0'){
        AddToList(CreateNode(message[i]));
        i++;
    }
    cursor = tail;

    for(int count = 0; count < N; count++){
        char operation, letter;
        scanf(" %c", &operation);
        if(operation == 'L'){
            CursorMoveLeft();
        }
        else if(operation == 'R'){
            CursorMoveRight();
        }
        else if(operation == 'D'){
            DeleteFromList();
        }
        else if(operation == 'I'){
            char c;
            scanf(" %c", &c);
            InsertToList(CreateNode(c));
        }
    }

    PrintList();
    printf("\n");
    return 0;
}
