#include <stdio.h>
#include <stdlib.h>
#include "CStub.h"

typedef int TESTTYPE;

IMPL_CSTUB(foo);

TESTTYPE foo_stub_1(TESTTYPE input)
{
    TESTTYPE a = input*2;
    printf("foo_stub_1\n");
    RETURN_VALUE(a);
}
TESTTYPE foo_stub_2(TESTTYPE input)
{
    printf("foo_stub_2\n");
    //RETURN_8bit(2);
    RETURN_VALUE(255);
}
TESTTYPE foo(TESTTYPE input)
{
    ENABLE_STUB(foo);
    printf("foo\n");
    return input;
}

int main()
{
    __asm__ __volatile__( "mov %0,%%rax;"::"i"(0xFFFFFFFFFFFFFFFF));
    printf("%d\n",foo(1));
    SETUP_STUB(foo,foo_stub_1);
    printf("%d\n",foo(2));
    RESET_STUB(foo);
    printf("%d\n",foo(3));
    SETUP_STUB(foo,foo_stub_2);
    printf("%d\n",foo(4));

    return 0;
}
/* EOF */
