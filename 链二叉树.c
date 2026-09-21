#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;                       // 节点存储的数据
    struct TreeNode *left;          // 左子树指针
    struct TreeNode *right;         // 右子树指针
} TreeNode;
TreeNode *create_node(int value) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode)); 
    if (node == NULL) {          
        printf("内存分配失败！\n");
        exit(1);                 
    }
    node->data  = value;         
    node->left  = NULL;         
    node->right = NULL;
    return node;                 
}

void preorder(TreeNode *root) {
    if (root == NULL) {          
        return;
    }
    printf("%d ", root->data);   
    preorder(root->left);       
    preorder(root->right);     
}

void inorder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);        
    printf("%d ", root->data);   
    inorder(root->right);       
}

void postorder(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);      
    postorder(root->right);    
    printf("%d ", root->data);  
}

int depth(TreeNode *root, int current_depth, int max_depth) {
    if (root == NULL) {
        
        return max_depth;
    }
    if (current_depth > max_depth) {
        max_depth = current_depth;   
    }
    int left_max  = depth(root->left,  current_depth + 1, max_depth);
    int right_max = depth(root->right, current_depth + 1, max_depth);
    return left_max > right_max ? left_max : right_max;
}

typedef struct Stack {
    TreeNode **arr;/*用来存放treenode*这个节点数组*/
    int top;/*栈顶的下标，每一步操作都只在栈顶进行*/
    int capacity;/*栈的最大容量*/
} Stack;
/*创建一个容量为capacity的栈*/
Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));/*申请栈结构体本体的内存*/
    stack->arr = malloc(sizeof(TreeNode *) * capacity);/*申请存放节点数组的内存*/
    stack->top = -1;/*-1表示当前是空栈*/
    stack->capacity = capacity;
    return stack;
}
/* 判断栈是否为空：栈顶还是 -1，说明没有任何元素 */
int isEmpty(Stack *stack) {
    return stack->top == -1;
}
/* 入栈：把一个节点指针压入栈顶（栈满则放弃，防止越界） */
void push(Stack *stack, TreeNode *node) {
    if (stack->top == stack->capacity - 1) {
        return;
    }
    stack->arr[++stack->top] = node;
}
/* 出栈：弹出并返回栈顶节点指针（空栈返回 NULL） */
TreeNode *pop(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;/*空栈返回NULL*/
    }
    return stack->arr[stack->top--];/*先取栈顶元素，然后再top减1，指示入栈的数量*/
}

void preorderTraversal(TreeNode *root)// 补全这个函数
{
if (root == NULL) {                 /* 空树直接返回 */
        return;
    }

    Stack *stack = createStack(100);    
    push(stack, root);                 /*把根压进栈*/

    while (!isEmpty(stack)) {           
        TreeNode *node = pop(stack);   /*立刻把栈顶弹出来*/
        printf("%d ", node->data);     /*弹出之后立刻打印根*/

        if (node->right != NULL) {    /*开始压孩子，采用先压右节点，后压左节点的形式*/
            push(stack, node->right);   /*根据lifo原理，后进栈的会先出栈，左孩子会先出栈*/
        }
        if (node->left != NULL) {      
            push(stack, node->left);    
        }
    }

    free(stack->arr);                  
    free(stack);                        
}

int main(void) {
    
    TreeNode *root   = create_node(1);   
    root->left       = create_node(2);
    root->right      = create_node(3);   
    root->left->left = create_node(4); 
    root->left->right  = create_node(5); 
    root->right->left  = create_node(6);
    root->right->right = create_node(7);

    printf("前序遍历（根左右）: ");
    preorder(root);           
    printf("\n");

    printf("中序遍历（左根右）: ");
    inorder(root);               
    printf("\n");

    printf("后序遍历（左右根）: ");
    postorder(root);                  
    printf("\n");

    printf("树的深度: %d\n",depth(root, 1, 0));           
    printf("空树的深度: %d\n",
           depth(NULL, 1, 0));         

    printf("用栈实现的非递归前序遍历: ");
    preorderTraversal(root);             
    printf("\n");

    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);
return 0;
}