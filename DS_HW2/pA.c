#include <stdio.h>
#include <stdbool.h>

int MaxHeap[300000] = {0};
int current = 0;

void InsertToHeap(int value){
    MaxHeap[current] = value;
    int tmpCurrent = current;
    int parent;
    
    while(tmpCurrent > 0){
        parent = (tmpCurrent - 1) / 2;
        if(MaxHeap[tmpCurrent] > MaxHeap[parent]){
            int tmp = MaxHeap[parent];
            MaxHeap[parent] = MaxHeap[tmpCurrent];
            MaxHeap[tmpCurrent] = tmp;
            tmpCurrent = parent;
        }
        else break;
    }
    current++;
}

void HeapUp(int idx){
    int tmpCurrent = idx;
    int parent;
    
    while(tmpCurrent > 0){
        parent = (tmpCurrent - 1) / 2;
        if(MaxHeap[tmpCurrent] > MaxHeap[parent]){
            int tmp = MaxHeap[parent];
            MaxHeap[parent] = MaxHeap[tmpCurrent];
            MaxHeap[tmpCurrent] = tmp;
            tmpCurrent = parent;
        }
        else break;
    }
}

void HeapDown(int idx){
    int parent = idx;

    while(1){
        int leftChild = parent * 2 + 1, rightChild = parent * 2 + 2, largerChild = parent;
        
        if(leftChild < current && MaxHeap[leftChild] > MaxHeap[largerChild])
            largerChild = leftChild;
        
        if(rightChild < current && MaxHeap[rightChild] > MaxHeap[largerChild])
            largerChild = rightChild;

        if(largerChild == parent) break;

        int tmp = MaxHeap[parent];
        MaxHeap[parent] = MaxHeap[largerChild];
        MaxHeap[largerChild] = tmp;
        parent = largerChild;
    }
}

int DeleteMax(){
    int maxValue = MaxHeap[0];
    MaxHeap[0] = MaxHeap[current - 1];
    MaxHeap[--current] = 0;
    HeapDown(0);
    return maxValue;
}

int main(){
    int numOfOperation;
    scanf("%d", &numOfOperation);
    for(int i = 0; i < numOfOperation; i++){
        int operation;
        scanf("%d", &operation);
        if(operation == 0){
            int value;
            scanf("%d", &value);
            InsertToHeap(value);
        }
        else if(operation == 1){
            int largest = DeleteMax();
            int secondLargest = DeleteMax();
            int value = largest - secondLargest;
            InsertToHeap(value);
        }
        else if(operation == 2){
            int idx, delta;
            scanf("%d %d", &idx, &delta);
            int oldValue = MaxHeap[idx];
            MaxHeap[idx] += delta;

            if(oldValue > MaxHeap[idx]){
                HeapDown(idx);
            }
            if(oldValue < MaxHeap[idx]){
                HeapUp(idx);
            }
        }
    }
    for(int i = 0; i < current; i++){
        printf("%d", MaxHeap[i]);
        if(i != current-1) printf(" ");
    }
    return 0;
}