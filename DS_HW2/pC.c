#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXLEN 10005
#define MAXTOK 10005

typedef struct Token {
    int type;   // 1 = number, 2 = operator, 3 = parentheses
    char ch;    // operator or parentheses
    int num;    // number
} Token;

typedef struct Node{
    int is_num; //1 for number and 2 for operator
    int num;
    char ch;
    struct Node* right;
    struct Node* left;
} Node;

Node* createOpNode(char op, Node* l, Node* r){
    Node* newNode = malloc(sizeof(Node));
    newNode->is_num = 0;
    newNode->ch = op;
    newNode->left = l, newNode->right = r;
    return newNode;
}

char op_stack[MAXTOK] = {0};
int op_top = 0;

Node* node_stack[MAXTOK] = {0};
int node_top = 0;

void char_push(char operator){
    op_stack[op_top++] = operator;
}
char char_pop(){
    return op_stack[--op_top];
}
bool charIsEmpty(){
    return op_top == 0;
}

Node* createNumNode(int val){
    Node* newNode = malloc(sizeof(Node));
    newNode->num = val;
    newNode->left = NULL, newNode->right = NULL;
    newNode->is_num = 1;
    return newNode;
}

void node_push(Node* t){
    node_stack[node_top++] = t;
}
Node* node_pop(){
    return node_stack[--node_top];
}
bool nodeIsEmpty(){
    return node_top == 0;
}

Token input[MAXTOK];
int input_len = 0;

void init() {
    for (int i = 0; i < MAXTOK; i++) {
        input[i].type = 0;
        input[i].ch = '\0';
        input[i].num = 0;
    }
}
void getInput() {
    char line[MAXLEN];
    fgets(line, sizeof(line), stdin);
    int len = strlen(line);
    for (int i = 0; i < len; i++) {
        char c = line[i];
        if (c == ' ')
            input_len += 1;
        else if ('0' <= c && c <= '9') {
            input[input_len].type = 1; // number
            input[input_len].num = input[input_len].num * 10 + (c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            input[input_len].type = 2; // operator
            input[input_len].ch = c;
        } else if (c == '(' || c == ')') {
            input[input_len].type = 3; // parentheses
            input[input_len].ch = c;
        } else {
            break; // end of line
        }
    }
    ++input_len;
}
void test() {
    printf("input length = %d\n", input_len);
    for (int i = 0; i < input_len; i++) {
        if (input[i].type == 1)
            printf("%d\n", input[i].num);
        else if (input[i].type == 2)
            printf("%c\n", input[i].ch);
        else
            printf("%c\n", input[i].ch);
    }
}
void printResult(int res) {
    printf("%d\n", res);
}

void printPrefix(Node* root){
    if(root == NULL) return;
    if(root->is_num == 1) printf("%d", root->num);
    else printf("%c", root->ch);
    printf(" ");
    printPrefix(root->left);
    printPrefix(root->right);
}

int priority(char op){
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
}

int cal(Node* root){
    if(root == NULL) return 0;
    if(root->is_num == 1) return root->num;
    int leftSub = cal(root->left);
    int rightSub = cal(root->right);
    if(root->left != NULL && root->right != NULL){
        if(root->ch == '+') return leftSub + rightSub;
        if(root->ch == '-') return leftSub - rightSub;
        if(root->ch == '*') return leftSub * rightSub;
        if(root->ch == '/') return leftSub / rightSub;
    }
}

Node* buildTree(){
    op_top = 0, node_top = 0;

    for(int i = 0; i < input_len; i++){

        if(input[i].type == 1){
            node_push(createNumNode(input[i].num));
        }

        else if(input[i].type == 2){
            char cur = input[i].ch;
            while(!charIsEmpty() && 
                op_stack[op_top-1] != '(' && 
                (priority(op_stack[op_top-1]) > priority(cur) ||
                priority(op_stack[op_top-1]) == priority(cur) )){
                    char op = char_pop();
                    Node* right = node_pop();
                    Node* left = node_pop();
                    node_push(createOpNode(op, left, right)); 
                }
            
            char_push(cur);
        }

        else if(input[i].type == 3){
            char ch = input[i].ch;
            if(ch == '('){
                char_push(ch);
            }
            else if(ch == ')'){
                while(!charIsEmpty() && op_stack[op_top-1] != '('){
                    char op = char_pop();
                    Node* right = node_pop();
                    Node* left = node_pop();
                    node_push(createOpNode(op, left, right)); 
                }

                if(!charIsEmpty() && op_stack[op_top-1] == '(') (void)char_pop();
            }
        }
        else continue;
    }

    while(!charIsEmpty()){
        char op = char_pop();
        Node* right = node_pop();
        Node* left = node_pop();
        node_push(createOpNode(op, left, right)); 
    }

    return node_pop();
}

int main() {
    init();
    getInput();
    //test(); // TODO: for testing, remember to delete it before submitting
    Node* root = buildTree();
    int res = 0;
    res = cal(root);
    printResult(res);
    printPrefix(root);
    return 0;
}