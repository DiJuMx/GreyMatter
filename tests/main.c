#include <stdio.h>
#include <stdlib.h>

void runTest();

int main(int argc, char *argv[])
{
        printf("Num args: %d, First arg: %s\n", argc, argv[0]);
        runTest(); 
        return EXIT_SUCCESS;
}
