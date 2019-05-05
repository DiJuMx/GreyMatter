#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GreyMatter/unit.h"
#include "GreyMatter/perceptron.h"

#define UNUSED(x) ((void)(x))

float tanh_deriv(float x)
{
        return 1.f/(coshf(x)*coshf(x));
}

int main(int argc, char*argv[])
{
        UNUSED(argc);
        UNUSED(argv);
        int status = 0; 
        struct gm_unit * layer1 = gmCreateUnit(2, 1);
        if (NULL == layer1){
                printf("Error creating unit\n");
                return EXIT_FAILURE;
        }

        status = gmCreatePerceptron(layer1, tanhf, tanh_deriv);
        if (-1 == status){
                printf("Error creating Perceptron\n");
                return EXIT_FAILURE;
        }

        

        return EXIT_SUCCESS;
}
