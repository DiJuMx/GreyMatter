#include <stdio.h>
#include <stdlib.h>

#define UNUSED(x) ((void)(x))

int main(int argc, char*argv[])
{
        UNUSED(argc);
        UNUSED(argv);
        printf("TEST RUN\n");
        return EXIT_SUCCESS;
}
