#include<assert.h>
#include<stdio.h>

#define push_stack(__arg, __stack) \
    __stack##_size++; \
     __stack[__stack##_size - 1] = arg;

enum {CALL, RET};

int fact(int arg)
{
    int fact_stack[256];
    int fact_stack_size = 0;
    int result = 1;

    if (arg == 0)
        return 1;
    assert(arg > 0);
    push_stack(arg, fact_stack);
    fact_stack_size = 1;
    
    int state = CALL;
    while(fact_stack_size)
    {
        if(state == RET)
        {
            arg = fact_stack[fact_stack_size - 1];
            fact_stack_size--;
            goto cont;
        }
        if(state == CALL)
        {
            arg = fact_stack[fact_stack_size - 1];
            if ( arg != 1 )
            {
                arg--;
                push_stack(arg, fact_stack);
            }else
            {
cont:
                fact_stack[fact_stack_size - 1] *= arg;
                state = RET;
            }
        }
    }
    result *= fact_stack[0];
    return result;
}

int main(void)
{
    printf("Fact = %d", fact(5));
    return 0;
}
