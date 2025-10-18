#include <stdio.h>
#include <string.h>
#include <time.h>

int L[500000] = {0};
int R[500000] = {0};
int val[500000] = {0};
int dummyHead = 0, dummyTail = 1, nextFree = 2;

static inline void InsertAfter(int pos, int value){
    int newNode = nextFree++;
    int right = R[pos];

    L[newNode] = pos;
    R[newNode] = right;
    val[newNode] = value;

    R[pos] = newNode;
    L[right] = newNode;
}

static inline void Delete(int index){
    int leftNode = L[index];
    int rightNode = R[index];
    R[leftNode] = rightNode;
    L[rightNode] = leftNode;
}

static inline void PrintList(){
    for(int i = R[dummyHead]; i != dummyTail; i = R[i]){
        printf("%d ", val[i]);
    }
    printf("\n");
}

int main(){
    //clock_t start = clock();
    R[dummyHead] = dummyTail;
    L[dummyTail] = dummyHead;

    int N, count;
    scanf("%d %d", &N, &count);
    int last = dummyHead;
    for(int i = 0; i < N; i++){
        int value;
        scanf("%d", &value);
        InsertAfter(last, value);
        last = R[last]; 
    }

    char operation[3];
    for(int i = 0; i < count; i++){
        scanf("%s", operation);
        int nodeValue, nodeIndex;
        if(operation[0] == 'H'){
            scanf("%d", &nodeValue);
            InsertAfter(dummyHead, nodeValue);
        }
        else if(operation[0] == 'T'){
            scanf("%d", &nodeValue);
            InsertAfter(L[dummyTail], nodeValue);
        }
        else if(operation[0] == 'A'){
            scanf("%d %d", &nodeIndex, &nodeValue);
            InsertAfter(nodeIndex + 1, nodeValue);
        }
        else if(operation[0] == 'B'){
            scanf("%d %d", &nodeIndex, &nodeValue);
            InsertAfter(L[nodeIndex+1], nodeValue);
        }
        else if(operation[0] == 'D'){
            scanf("%d", &nodeIndex);
            Delete(nodeIndex + 1);
        }
        else if(operation[1] == 'H'){
            scanf("%d", &nodeIndex);
            int target = nodeIndex + 1;

            Delete(target);

            int right = R[dummyHead];
            L[right] = target;
            R[dummyHead] = target;
            L[target] = dummyHead;
            R[target] = right;
        }
        else if(operation[1] == 'T'){
            scanf("%d", &nodeIndex);
            int target = nodeIndex + 1;

            Delete(target);

            int left = L[dummyTail];
            R[left] = target;
            L[target] = left;
            R[target] = dummyTail;
            L[dummyTail] = target;
        }
    }
    if(R[dummyHead] != dummyTail && L[dummyTail] != dummyHead){
        PrintList();
        for(int i = L[dummyTail]; i != dummyHead; i = L[i]){
            printf("%d ", val[i]);
        }
        printf("\n");
    }
    else printf("EMPTY\nEMPTY\n");
/*
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", time_spent);
*/
    return 0;
}
