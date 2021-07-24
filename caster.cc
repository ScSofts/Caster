#include "caster.h"
#define ASMJIT_STATIC
#include <asmjit/asmjit.h>
#include <unordered_map>

namespace  {
    thread_local asmjit::JitRuntime *jrt;

    std::unordered_map<void*,asmjit::CodeHolder*> function_map;
};

extern "C"{
    void init(){
        jrt = new asmjit::JitRuntime();
    }

    void free_function(void* function){
        auto x = function_map[(void*)function];
        if(x){
            delete x;
        }
    }


    void* bind_function(void* function, void* this_ptr){
        asmjit::CodeHolder *ch = new asmjit::CodeHolder();
        ch->init(jrt->environment());
        asmjit::x86::Assembler as(ch);
        as.pop(asmjit::x86::regs::ebx);
        as.mov(asmjit::x86::regs::ecx, this_ptr);
        as.call(function);
        as.push(asmjit::x86::regs::ebx);
        as.ret();
        void *func;
        jrt->add(&func, ch);
        function_map[(void*)func] = ch;
        return func;
    }
};