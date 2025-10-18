#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
    int key;
    struct node* left;
    struct node* right; 
} node;

node* queue[3000];
int  front = 0, rear = 0;

void enqueue(node* node){
    queue[rear++] = node;
}

void dequeue(){
    queue[front++] = NULL;
}

bool isEmpty(){
    return (front == rear);
}

void levelOrder(node* root){
    enqueue(root);
    do{
        printf("%d ", queue[front]->key);
        if(queue[front]->left != NULL){
            enqueue(queue[front]->left);
        }
        if(queue[front]->right != NULL){
            enqueue(queue[front]->right);
        }
        dequeue();
    } while(!isEmpty());
}

node* createNode(int key){
    node* newNode = malloc(sizeof(node));
    newNode->key = key;
    newNode->left = NULL, newNode->right = NULL;

    return newNode;
}

node* insert(node* root, int key){
    if(root == NULL){
        root = createNode(key);
        return root;
    } 
    else{
        if(key > root->key)
            root->right = insert(root->right, key);
            
        else
            root->left = insert(root->left, key);
    }

    return root;
}

void inorder(node* root){
    if(root != NULL){
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

node* delete(node* root, int deleteKey){
    if(root->key == deleteKey){
        if(root->right == NULL && root->left == NULL){
            free(root);
            return NULL;
        } 
        else if(root->right != NULL && root->left == NULL){
            node* r = root->right;
            free(root);
            return r;
        }
        else if(root->right == NULL && root->left != NULL){
            node* l = root->left;
            free(root);
            return l;
        }
        else{
            node* replacedNode = root->right;
            while(replacedNode->left != NULL){
                replacedNode = replacedNode->left;
            }
            root->key = replacedNode->key;
            root->right = delete(root->right, replacedNode->key);
            return root;
        }
    }
    else if(deleteKey > root->key){
        root->right = delete(root->right, deleteKey);
        return root;
    }
               
    else{
        root->left = delete(root->left, deleteKey);
        return root;
    }
        
}

int main(){
    char command[10];
    node* root = NULL;
    scanf("%s", command);
    while(strcmp(command, "exit") != 0){
        if(strcmp(command, "insert") == 0){
            int keyValue;
            scanf("%d", &keyValue);
            root = insert(root, keyValue);
        }
        if(strcmp(command, "delete") == 0){
            int keyValue;
            scanf("%d", &keyValue);
            root = delete(root, keyValue);
        }
        scanf("%s", command);
    }

    //printf("Level Order traversal: ");
    levelOrder(root);
    printf("\n");
    return 0;
}