#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TREE_SIZE 100
/*
 * 顺序存储二叉树结点
 * - data：结点数据
 * - used：当前位置是否有结点
 */
typedef struct {
    int data;
    bool used;
} SeqTreeNode;

/*
 * 顺序存储二叉树
 * - nodes：结点数组
 * - size：数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;

void init_tree(SeqBiTree *tree) {
tree->size = MAX_TREE_SIZE;
for (int i = 0; i < MAX_TREE_SIZE; i++) {
        tree->nodes[i].data = 0;
        tree->nodes[i].used = false;
    }
}
bool set_root(SeqBiTree *tree, int value) {
    if (1 >= tree->size) {
        return false;             
    }
    tree->nodes[1].data = value;  
    tree->nodes[1].used = true;    
    return true;
}
bool set_left_child(SeqBiTree *tree, int parent_node, int value) {
    int child = 2 * parent_node;
    if (parent_node < 1 || parent_node >= tree->size) return false;
    if (!tree->nodes[parent_node].used)              return false;
    if (child >= tree->size)                         return false;

    tree->nodes[child].data = value;
    tree->nodes[child].used = true;
    return true;
}
bool set_right_child(SeqBiTree *tree, int parent_node, int value) {
    int child = 2 * parent_node + 1;   

    if (parent_node < 1 || parent_node >= tree->size) return false;
    if (!tree->nodes[parent_node].used)               return false;
    if (child >= tree->size)                          return false;

    tree->nodes[child].data = value;
    tree->nodes[child].used = true;
    return true;
}
void level_order(SeqBiTree *tree) {
    int last_used = 0;
    for (int i = 1; i < tree->size; i++) {
        if (tree->nodes[i].used) {
            last_used = i;
        }
    }
    if (last_used == 0) {
        printf("(空树)\n");
        return;
    }
    int start = 1;
    while (start <= last_used) {                 
        int end = 2 * start - 1;               
        if (end >= tree->size) end = tree->size - 1;
        for (int i = start; i <= end; i++) {
            if (tree->nodes[i].used) {
                printf("%d ", tree->nodes[i].data);   
            } else {
                printf("-1 ");                    
            }
        }
        printf("\n");                        

        start = end + 1;                   
    }
}

int main(void) {
    SeqBiTree tree;
    init_tree(&tree); 

    set_root(&tree, 1);  
    set_left_child(&tree, 1, 2); 
    set_right_child(&tree, 1, 3); 
    set_left_child(&tree, 2, 4); 
    set_right_child(&tree, 2, 5); 
    set_left_child(&tree, 3, 6);
    set_right_child(&tree, 3, 7);
    printf("层序遍历结果（每行一层，空节点打印 -1）：\n");
    level_order(&tree);
    
    SeqBiTree tree2;
    init_tree(&tree2);
    set_root(&tree2, 1);
    set_left_child(&tree2, 1, 2);
    set_right_child(&tree2, 2, 5);

    printf("\n带空节点的层序遍历结果：\n");
    level_order(&tree2);


    return 0;
}


