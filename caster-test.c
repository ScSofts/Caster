#include <stdio.h>
#include <malloc.h>
#include "caster.h"

struct _io;
STRUCT_ALIAS(_io, IO);
DECLARE_MEMBER_TYPE(IO *, io_p,void);

struct _io{
    io_p p1;
    io_p p2;
    int i1;
    int i2;
};

DEFINE_MEMBER_FUNC(IO*,_io_p1,IO* const this){
    printf("1 + %d\n", this->i1);
    return this;
}

DEFINE_MEMBER_FUNC(IO* ,_io_p2,IO* const this){
    printf("2 + %d\n", this->i2);
    return this;
}

void io_constructor(IO* io){
    io->p1 = (io_p)bind_function((void*)_io_p1, (void*)io);
    io->p2 = (io_p)bind_function((void*)_io_p2, (void*)io);
    io->i1 = 123;
    io->i2 = 456;
}

void io_destructor(IO* io){
    free_function(io->p1);
    free_function(io->p2);
    free(io);
    printf("destructor called!");
}


int main(){
    init();

    IO *io = (IO*)malloc(sizeof(IO));
    io_constructor(io);

    io
    ->p1()
    ->p2()
    ->p2()
    ->p1()
    ->p2();

    io_destructor(io);
    return 0;
}