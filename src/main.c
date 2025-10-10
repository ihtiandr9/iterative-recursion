#include<assert.h>
#include<stdio.h>

#define push_stack(__cn, __stack) \
    __stack##_size++; \
     __stack[__stack##_size - 1] = __cn;

enum {CALL, RET};
typedef struct
{
    int arg;
    int result;
    void *retlabel;
}context;

int fact(int arg)
{
    context fact_stack[256];
    int fact_stack_size = 0;
    int result = 1;

    if (arg == 0)
        return 1;
    assert(arg > 0);
    context cn;
    cn.result = 1;
    cn.arg = arg;
    cn.retlabel = 0;
     
    push_stack( cn, fact_stack);
    fact_stack_size = 1;
    
    int state = CALL;
    while(fact_stack_size)
    {
func:
        if(state == RET)
        {
            cn = fact_stack[fact_stack_size];
            // drop 1c frame here
            goto *cn.retlabel;
        }
        if(state == CALL)
        {
            if ( fact_stack[fact_stack_size - 1].arg == 1)
            {
                fact_stack[fact_stack_size - 1].result = 1;
                state=RET;
                goto retfunc;
            }else
            {
                cn.arg--;
                cn.retlabel = &&cont;
                push_stack(cn, fact_stack);
                state = CALL;
                goto func;
            }

cont:
            fact_stack[fact_stack_size - 1].result =
                fact_stack[fact_stack_size - 1].arg
                * cn.result;
            state = RET;
            goto retfunc;
        }
retfunc:
        fact_stack_size--;
    }
    result *= fact_stack[0].result;
    return result;
}

int main(void)
{
    printf("Fact = %d\n", fact(5));
    return 0;
}
