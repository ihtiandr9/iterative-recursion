#include<assert.h>
#include<stdio.h>

#define MAX_STACK_DEPTH 255
#define push_stack(__cn, __stack) \
    __stack##_size++; \
     __stack[__stack##_size - 1] = __cn;

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
    int fact_stack_size = 0;
    int result = 1;

    assert(arg > 0);
    context cn;
    cn.result = 1;
    cn.arg = arg;
    cn.retlabel = MAX_STACK_DEPTH;
     
    push_stack( cn, fact_stack);
    fact_stack_size = 1;
    
    int state = CALL;

    while(fact_stack_size)
    {
        if(state == RET)
        {
            cn = fact_stack[fact_stack_size - 1];
            fact_stack_size--;
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
                fact_stack[fact_stack_size - 1].result =
                    fact_stack[fact_stack_size - 1].arg
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
