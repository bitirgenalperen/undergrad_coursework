#include <stdio.h>
#include <math.h>
#include "the1.h"

/*
 * This function gets a parameter that indicateswhether user will give initial values or not. If it evaluates false,
 * you will simply set all values of thearray -1. Otherwise, you will scan an integer from the user stating the number
 * of values that s/he willenter. User will enter that many integer index and value pairs. If the value for that index
 * is insertedbefore, or the index or the value is out of the range, you will simply ignore it.
*/
void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user) {
    /* Silence is golden */
}


/*
 * This function gets index of parent node, 'l'eft, 'r'ight or 'i'tself for where to insert and integer value.
 * If the value for the inserted node already exists, it ignores and does nothing.
 */
void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value) {
    /* Silence is golden */
}


/*
 * This method  gets  the  index  of  the  node  to  be  deleted.   If  a  node  is  to  be deleted, all of its
 * descendants will be also purged.  Deleting means putting -1 value to the proper area in the array.
 */
void delete_node_rec(int binary_tree[MAX_LENGTH], int node) {
    /* Silence is golden */
}


/*
 * This is  a recursive function that prints the tree in in-order fashion. In other words, it will print the nodes 
 * starting from the left-most child and traverse the rest of the tree in that manner. Printing order will be 
 * <left-child, root, right-child>. It gets the index of the root and the depth value as control variable. Initial 
 * value of the depth will be the height of the tree. Be careful, any sub-tree can be given to the function.
 */
void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) {
    /* Silence is golden */
}

/*
 * This is a recursive function that returns the height of the tree.  If given root does not have any child, its height
 * is 0.  Be careful, any sub-tree can be given to the function
 */
int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    return 0;
}

/*
 * This is a recursive function that returns the minimum value given tree contains.
 * Be careful, any sub-tree can be given to the function.
 */
int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    return MIN_VAL;
}

/*
 * This is an iterative function that performs breadth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  it returns the index of the first observation of the value.
 * It gets the index of the root and the integer value that is to be searched.  Be careful, any sub-tree can be given to
 * the function and you will apply level-wise search in the tree
 */
int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value) {
    return -1;
}

/*
 * This is  a  recursive  function  that  performs  depth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  itreturns the index of the first observation of the value.  It gets
 * the index of the root and the integer valuethat is to be searched.
 * Be careful, any sub-tree can be given to the function.
 */
int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) {
    return -1;
}

/*
 * This is already given to you.
 */
void print_binary_tree_values(int binary_tree[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }

}

