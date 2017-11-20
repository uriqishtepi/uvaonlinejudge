#include <stdio.h>

typedef struct node_t node_t;
struct node_t {
    struct node_t * left; /* null if current node is leaf */
    struct node_t * right;
    int data;
} ;

/* this simple isBst version does not work because
 * it would not detect this non-bst tree:
 *      4
 *     /
 *    3
 *   / \
 *  2   5
 *
 */
int isBst_wrong(node_t *n)
{
    if (n == NULL) return 1;

    if (n->right && n->right->data < n->data)
        return 0;
    if(isBst(n->left) && n->left->data > n->data)
        return 0;

    if (isBst(n->right) && isBst(n->left) )
        return 1;

    return 0;
}

/* get n-th node of a bst
 * start at the leftmost child and count in-order
 * to number nodes, stop when we find n-th.
 * In-order traversal: process left, then curr, then right
 */
node_t *getNth(node_t *n, int order, int *location)
{
    if (n->left) {
        node_t * l = getNth(n->left, order, location);
        if(l != NULL) {
            return l;
        }
    }
    
    /* this node's location is location + 1 */
    (*location)++;
    if (order == *location)
        return n;
    
    if(n->right) {
        node_t * r = getNth(n->right, order, location);
        if(r != NULL) {
            return r;
        }
    }

    return NULL;
}

/* return one based location (leftmost node has order of 1 */
node_t *getOrder(node_t *n, int order)
{
    if (order <= 0) return NULL;
    int location = 0;
    return getNth(n, order, &location);
}


int main()
{
    return 0;
}
