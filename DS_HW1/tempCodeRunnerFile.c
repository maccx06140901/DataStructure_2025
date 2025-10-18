#include <stdio.h>
#include <string.h>

typedef struct node{
    int id, value;
    struct node *prev, *next;
}Node;

int L[250000] = {0};
int R[250000] = {0};
long long int val[250000] = {0};
int dummyHead = 0, dummyTail = 1, nextFree = 2;

void InsertAfter(int pos, int value){
    int newNode = nextFree++;
    int right = R[pos];

    L[newNode] = pos;
    R[newNode] = right;
    val[newNode] = value;

    R[pos] = newNode;
    L[right] = newNode;
}

void Delete(int index){
    int leftNode = L[index];
    int rightNode = R[index];
    R[leftNode] = rightNode;
    L[rightNode] = leftNode;
}

void PrintList(){
    for(int i = R[dummyHead]; i != dummyTail; i = R[i]){
        printf("%lld ", val[i]);
    }
    printf("\n");
}

int main(){
    R[dummyHead] = dummyTail;
    L[dummyTail] = dummyHead;

    int N, count;
    scanf("%d %d", &N, &count);
    int last = dummyHead;
    for(int i = 0; i < N; i++){
        int value;
        scanf("%d", &value);
        InsertAfter(last, value);
        last = R[last]; // 將最後一個插入的節點更新為新節點
    }
/*
    char operation[3];
    for(int i = 0; i < count; i++){
        scanf("%s", operation);
        int nodeValue, nodeIndex;
        if(strcmp(operation, "H") == 0){
            scanf(" %d\n", &nodeValue);
        }
        else if(strcmp(operation, "T") == 0){
            scanf(" %d\n", &nodeValue);
        }
        else if(strcmp(operation, "A") == 0){

        }
        else if(strcmp(operation, "B") == 0){

        }
        else if(strcmp(operation, "D") == 0){

        }
        else if(strcmp(operation, "MH") == 0){

        }
    }*/
    PrintList();
    return 0;
}