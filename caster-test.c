#include <stdio.h>
#include "caster.h"

DECLARE_MEMBER_TYPE(void, io_print,int);
struct _io{
    const char *buf;
    io_print printBuf;
};
STRUCT_ALIAS(_io, IO);

DEFINE_MEMBER_FUNC(void,_io_printBuf,IO* io,int i){
    printf("&(io->buf)=%p\n", io->buf);
    printf("io->buf=%s\n", io->buf);
    printf("i=%d,j=%d\n",i, 5);
    io->buf = NULL;
}

void io_constructor(IO* io){
    io->printBuf = (io_print)bind_function((void*)_io_printBuf, (void*)io);
}

void io_destructor(IO* io){
    free_function(io->printBuf);
    printf("destructor called!");
}


int main(){
    init();

    AUTO_DESTRUCT(io_destructor) IO io;

    io_constructor(&io);
    // printf("%p",io.printBuf);
    io.buf = "Hello World!";
    io.printBuf(4);

    printf("&(io->buf)=%p\n", io.buf);
    return 0;
}