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
     
    push_stack( cn, fact_stack);
    fact_stack_size = 1;
    
    int state = CALL;
    while(fact_stack_size)
    {
func:
        if(state == RET)
        {
            goto cont;
        }
        if(state == CALL)
        {
            if ( fact_stack[fact_stack_size - 1].arg == 1)
            {
                fact_stack[fact_stack_size - 1].result = 1;
                fact_stack_size--;
                state=RET;
                continue;
            }else
            {
                cn.arg--;
                push_stack(cn, fact_stack);
                state = CALL;
                goto func;
            }

cont:
            fact_stack[fact_stack_size - 1].result =
                fact_stack[fact_stack_size - 1].arg
                * fact_stack[fact_stack_size].result;
            fact_stack_size--;
            state = RET;
        }
    }
    result *= fact_stack[0].result;
    return result;
}

int main(void)
{
    printf("Fact = %d\n", fact(5));
    return 0;
}
