/*
 *
 *
 * */
#include<assert.h>
#include<stdio.h>

#define MAX_STACK_DEPTH 256
#define push_stack(__cn, __stack) \
    __stack##_top++; \
    __stack[__stack##_top] = __cn;

enum {CALL, RETLABEL1, RETLABEL2, RET};
typedef struct tree tree;
struct tree
{
    tree *left;
    tree *right;
    int value;
};

typedef struct
{
    tree *arg;
    int result;
    int retlabel;
}context;

int traverse(tree* arg)
{
    context tree_stack[MAX_STACK_DEPTH];
    int tree_stack_top = -1;
    int result = 0;

    assert(arg > 0);
    context cn, *prev_cn = 0;
    cn.result = result;
    cn.arg = arg;
    cn.retlabel = RET;
     
    push_stack( cn, tree_stack);
    
    int state = CALL;

    while( tree_stack_top >=0 )
    {
        if(state == RET)
        {
            prev_cn = &tree_stack[tree_stack_top];
            state = prev_cn->retlabel;
            tree_stack_top--;
            if ( tree_stack_top >= 0)
                cn = tree_stack[tree_stack_top];
        }

        if( state < RETLABEL1 )
        {
            if ( cn.arg -> left )
            {
                cn.arg = cn.arg -> left;
                cn.result = 0;
                cn.retlabel = RETLABEL1;
                push_stack(cn, tree_stack);
                state = CALL;
                continue;
            }
        }
        if( state < RETLABEL2 )
        {
            if( state == RETLABEL1 )
            {
                printf("LeftValue = %d\n", prev_cn->arg->value);
            }
            if ( cn.arg -> right )
            {
                cn.arg = cn.arg -> right;
                cn.result = 0;
                cn.retlabel = RETLABEL2;
                push_stack(cn, tree_stack);
                state = CALL;
                continue;
            }
        }

        if (state < RET )
        {
            if (state == RETLABEL2)
            {
                printf("RightValue = %d\n", prev_cn->arg->value);
            }
        }
        state = RET;
    }
    printf("RootValue = %d\n", cn.arg->value);
    result *= cn.result;
    return result;
}

int main(void)
{
    tree right;
    right.value = 3;
    right.left = NULL;
    right.right = NULL;

    tree leftright;
    leftright.value = 4;
    leftright.left = NULL;
    leftright.right = NULL;
    
    tree left;
    left.value = 1;
    left.left = NULL;
    left.right = &leftright;

    tree root;
    root.value = 2;
    root.left = &left;
    root.right = &right;

    traverse(&root);
    return 0;
}
