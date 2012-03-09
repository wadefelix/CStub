#ifndef _CSTUB_H_
#define _CSTUB_H_

typedef struct tagCStub {
    int run_times;
    void* func_ptr;
} CStub;

#define IMPL_CSTUB(func_name) CStub func_name##_stub = {0,NULL}
#define DECL_CSTUB(func_name) extern CStub func_name##_stub

#define SETUP_STUB(func_name,a_stub_of_func) func_name##_stub.func_ptr = a_stub_of_func
#define RESET_STUB(func_name) func_name##_stub.func_ptr = NULL


/* 24: 32-bit, VC no purecoverage */
/* 35: 32-bit, VC with purecoverage's function stats */
/* 46: 32-bit, VC with purecoverage's function stats and line stats*/
/* 4 : 64-bit, Code::Blocks(gcc) on ubuntu, No Optimize */
#define SKIP_INSTRUCTIONS_NUM 4

#define ENABLE_STUB(func_name) \
if (NULL!=func_name##_stub.func_ptr)            \
{                                               \
    func_name##_stub.run_times ++;              \
    __asm__ __volatile__(\
        "mov %0,%%rcx;"    \
        "add %1,%%rcx;"         \
        "jmp %%rcx;"                               \
    ::"c"(func_name##_stub.func_ptr),"i"(SKIP_INSTRUCTIONS_NUM));                                           \
}

#define RETURN_VOID()   \
__asm__ __volatile__(\
 "pop %rdi;"\
 "pop %rsi;"\
 "pop %rbx;"\
 "mov %rbp,%rsp;"\
 "pop %rbp;"\
 "ret;"\
)

#define RETURN_8bit(value)   \
__asm__ __volatile__(\
 "mov %0,%%al;"\
 "pop %%rdi;"\
 "pop %%rsi;"\
 "pop %%rbx;"\
 "mov %%rbp,%%rsp;"\
 "pop %%rbp;"\
 "ret;"\
 ::"ai"(value)\
)
#define RETURN_16bit(value)   \
__asm__ __volatile__(\
 "mov %0,%%ax;"\
 "pop %%rdi;"\
 "pop %%rsi;"\
 "pop %%rbx;"\
 "mov %%rbp,%%rsp;"\
 "pop %%rbp;"\
 "ret;"\
 ::"ai"(value)\
)
#define RETURN_32bit(value)   \
__asm__ __volatile__(\
 "mov %0,%%eax;"\
 "pop %%rdi;"\
 "pop %%rsi;"\
 "pop %%rbx;"\
 "mov %%rbp,%%rsp;"\
 "pop %%rbp;"\
 "ret;"\
 ::"ai"(value)\
)
#define RETURN_64bit(value)   \
__asm__ __volatile__(\
 "mov %0,%%rax;"\
 "pop %%rdi;"\
 "pop %%rsi;"\
 "pop %%rbx;"\
 "mov %%rbp,%%rsp;"\
 "pop %%rbp;"\
 "ret;"\
 ::"ai"(value)\
)

#if defined(__LP64__)/*gcc*/ || defined(__64BIT__)/*IBM XL*/ || defined(_LP64)/*gcc*/ || (__WORDSIZE == 64)/*gcc*/
    #define RETURN_VALUE(value)   \
        do{\
        long local_value = (long)(value);\
        RETURN_64bit(local_value);\
        }while(0)
#else
    #define RETURN_VALUE(value)   \
        do{\
        long local_value = (long)(value);\
        RETURN_32bit(local_value);\
        }while(0)
#endif

#endif /* #ifndef _CSTUB_H_ */
/* EOF */
