#include<assert.h>
#include<stdio.h>

#define MAX_STACK_DEPTH 255
#define push_stack(__cn, __stack) \
    __stack##_top++; \
     __stack[__stack##_top] = __cn;

enum {CALL, RET};
typedef struct
{
    int arg;
    int result;
    int retlabel;
}context;

int fact(int arg)
{
    context fact_stack[256];
    int fact_stack_top = -1;
    int result = 1;

    assert(arg > 0);
    context cn;

    cn.result = 1;
    cn.arg = arg;
    cn.retlabel = MAX_STACK_DEPTH;
     
    push_stack( cn, fact_stack);
    
    int state = CALL;

    while(fact_stack_top >= 0)
    {
        if(state == RET)
        {
            cn = fact_stack[fact_stack_top];
            fact_stack_top --;
            // drop 1c frame here
        }

        if(state == CALL || cn.retlabel < 1)
        {
            if ( cn.arg == 1)
            {
                cn.result = 1;
                state=RET;
                continue;
            }else
            {
                cn.arg--;
                cn.retlabel = 1;
                push_stack(cn, fact_stack);
                state = CALL;
                continue;
            }
        }

            if (state == RET && cn.retlabel == 1)
            {
                fact_stack[fact_stack_top].result =
                    fact_stack[fact_stack_top].arg
                    * cn.result;
            }
    }
    result *= cn.result;
    return result;
}

int main(void)
{
    printf("Fact = %d\n", fact(5));
    return 0;
}
