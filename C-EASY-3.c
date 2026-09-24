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
} SeqTreeNode;/*创建一个结构体，存放数值域和一个bool量（判断每一个节点是否是空节点）*/

/*
 * 顺序存储二叉树
 * - nodes：结点数组
 * - size：数组最大容量
 */
typedef struct {
    SeqTreeNode nodes[MAX_TREE_SIZE];
    int size;
} SeqBiTree;/*创建一个结构体中存放节点数组和数组的最大容量*/
/*这两个结构体，前者用来描述一个节点，而后者用来描述整棵树*/

void init_tree(SeqBiTree *tree) {
tree->size = MAX_TREE_SIZE;
for (int i = 0; i < MAX_TREE_SIZE; i++) {
        tree->nodes[i].data = 0;
        tree->nodes[i].used = false;
    }
}/*作用是初始化整棵树，设定好二叉树的大小，将逐个位置进行清空，data归零*/
/*用第一个结构体中的bool量，used，去排除所有没有节点的位置*/

bool set_root(SeqBiTree *tree, int value) {
    if (1 >= tree->size) {
        return false;             
    }
    tree->nodes[1].data = value;  
    tree->nodes[1].used = true;    
    return true;
}/*用来固定根节点，将根节点的下标确定为1，并且确保数组可以放得下*/

bool set_left_child(SeqBiTree *tree, int parent_node, int value) {
    int child = 2 * parent_node;
    if (parent_node < 1 || parent_node >= tree->size) return false;
    if (!tree->nodes[parent_node].used)              return false;
    if (child >= tree->size)                         return false;

    tree->nodes[child].data = value;
    tree->nodes[child].used = true;
    return true;
}/*用来帮助整棵树进行延伸，设置左孩子，主要利用的是根节点为i，左节点为2i，右节点为2i+1*/
/*同时用if条件确保孩子节点一定有对应的父节点，且孩子节点的下标不会出现越界的情况，最后去给孩子节点赋值value*/

bool set_right_child(SeqBiTree *tree, int parent_node, int value) {
    int child = 2 * parent_node + 1;   

    if (parent_node < 1 || parent_node >= tree->size) return false;
    if (!tree->nodes[parent_node].used)               return false;
    if (child >= tree->size)                          return false;

    tree->nodes[child].data = value;
    tree->nodes[child].used = true;
    return true;
}/*同左孩子*/

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
}/*遍历函数，作用是按节点下标打印整棵树，节点为空则打印-1，且每打印一行换行*/
/*函数的第一步是找出整棵树的最后一个节点，从而可以知道打印到了多少层*/
/*是否为空树两个信息然后设置start=1，即可利用while循环开始遍历整棵树*/
/*并且通过遍历可以给所有的空节点在输出时变为负数，从而可以较为容易的分析每个节点的状态*/

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

