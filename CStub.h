#ifndef _CSTUB_H_
#define _CSTUB_H_

typedef struct tagCStub {
    int run_times;
    void* func_ptr;
} CStub;

/**
* 定义桩数据结构
*/
#define IMPL_CSTUB(func_name) CStub func_name##_stub = {0,NULL}
#define DECL_CSTUB(func_name) extern CStub func_name##_stub

/**
* 指定桩函数使用指定功能的实现函数
*/
#define SETUP_STUB(func_name,a_stub_of_func) func_name##_stub.func_ptr = a_stub_of_func
#define RESET_STUB(func_name) func_name##_stub.func_ptr = NULL


/* 24: 32-bit, VC no purecoverage */
/* 35: 32-bit, VC with purecoverage's function stats */
/* 46: 32-bit, VC with purecoverage's function stats and line stats*/
/* 4 : 64-bit, Code::Blocks(gcc) on ubuntu, No Optimize */
#define SKIP_INSTRUCTIONS_NUM 4

/**
* 桩函数内使用，用来调用被安装的具有指定功能的实现函数
*/
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


#endif /* #ifndef _CSTUB_H_ */
/* EOF */
