#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 200000

int number[MAX_SIZE] = {0};
int distance[MAX_SIZE] = {0};
int stack[MAX_SIZE] = {0};
int stackTop = -1, disCurrent = 0;

bool StackIsEmpty(){
    return (stackTop >= 0)?false:true;
}

bool StackIsFull(){
    return (stackTop == MAX_SIZE-1)?true:false;
}

void StackPush(int item){
    if(StackIsFull()) return;

    else{
        stack[++stackTop] = item;
    }
    return;
}

void StackPop(){
    if(stackTop == -1) return;

    else{
        stackTop--;
         return;
    }
}

int StackTop(){
    return stack[stackTop];
}

void PrintStack(){
    if(StackIsEmpty()) return;

    for(int i = 0; i < stackTop; i++){
        printf("%d ", stack[i]);
    }
    return;
}

int main(){
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d", &number[i]);
    }

    for(int i = 0; i<N; i++){
        while(!StackIsEmpty() && number[StackTop()] >= number[i]){
            //printf("-1 ");
            StackPop();
        }

        if(StackIsEmpty()){
            printf("-1 ");
        }
        //if(number[StackTop()] < number[i]){
        else{
            printf("%d ", i-StackTop());
            distance[disCurrent++] = i - StackTop();
            //StackPush(i);
        }
        StackPush(i);
    }
    
/*
    for(int i = 0; i<N; i++){
        if(StackIsEmpty()){
            printf("-1 ");
            StackPush(number[i]);
        }
        else{
            int j = stackTop, dis = 0, find = 0;
            while(find != 1){//TODO
                if(StackIsEmpty()){
                    printf("-1 ");
                    break;
                }
                dis++;
                if(number[i] > stack[j--]){
                    distance[disCurrent++] = dis;
                    printf("%d ", dis);
                    find = 1;
                }
                else{
                    StackPop();
                }
            }
        }
    }
*/
    printf("\n");

    if(disCurrent == 0){
        printf("EMPTY");
    }
    else{
        for(int i = 0; i < disCurrent; i++){
            printf("%d ", distance[i]);
        }
    }

    return 0;
}

