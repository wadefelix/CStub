[CStub](https://github.com/wadefelix/CStub)
============
创建此库用于尝试在C语言中建立单元测试用的各种桩函数。

在Ubuntu 11.10 64-bit上的[Code::Blocks](http://www.codeblocks.org/)中测试基本可用。  
gcc (Ubuntu/Linaro 4.6.1-9ubuntu3) 4.6.1

使用注意事项
----------
请禁用编译器的优化选项


    /**
    * 定义桩数据结构
    */
    #define IMPL_CSTUB(func_name) CStub func_name##_stub = {0,NULL}

    /**
    * 指定桩函数使用指定功能的实现函数
    */
    #define SETUP_STUB(func_name,a_stub_of_func) func_name##_stub.func_ptr = a_stub_of_func

    /**
    * 桩函数内使用，用来调用被安装的具有指定功能的实现函数
    */
    #define ENABLE_STUB(func_name) \


See test.c for example.
