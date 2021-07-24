#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C"{
#endif

void init();
void free_function(void* function);
void* bind_function(void* function, void* this_ptr);


#define DECLARE_MEMBER_TYPE(RetType, Name, ...) typedef RetType(__stdcall*Name)(__VA_ARGS__);

#define DEFINE_MEMBER_FUNC(RetType,Name,...) static RetType __thiscall Name(__VA_ARGS__)

#define STRUCT_ALIAS(Original,Alias) typedef struct Original Alias;

#define AUTO_DESTRUCT(destructor) __attribute__((cleanup(destructor)))
#ifdef __cplusplus
};
#endif