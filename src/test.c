#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "GreyMatter/unit.h"
#include "GreyMatter/summation.h"

float tanh_deriv(float x)
{
        return 1.f/(coshf(x)*coshf(x));
}

int main(int argc, char*argv[])
{
        UNUSED(argc);
        UNUSED(argv);

        int status = 0;

        float weights[] = {.1f, .5f, .5f};
        float inputs[] = {1.f, 1.f, 1.f};

        struct gm_unit layer1 = {0};

        status = gmCreateUnit(&layer1, 3, 1);

        if (0 > status){
                printf("Error creating unit -- Err: %d\n", status);
                return EXIT_FAILURE;
        }

        status = gmCreateSummation(&layer1);
        if (0 > status){
                printf("Error creating summation -- Err: %d\n", status);
                return EXIT_FAILURE;
        }

        layer1.input[0] = &inputs[0];
        layer1.input[1] = &inputs[1];
        layer1.input[2] = &inputs[2];

        layer1.forwardPass(&layer1);

        printf("Inputs:  %2.2f %2.2f %2.2f\n", 
                        inputs[0], inputs[1], inputs[2]);
        printf("Output:  %2.4f\n", 
                        layer1.output[0]); 
        printf("Expect:  %2.4f\n", 
                        inputs[0] + inputs[1] + inputs[2]);

        gmCleanupSummation(&layer1);

        printf("-------\n");

        status = gmCreateWeightedSummation(&layer1);
        if (0 > status){
                printf("Error creating summation -- Err: %d\n", status);
                return EXIT_FAILURE;
        }

        status = gmSetSummationWeights(&layer1, weights);
        if (0 > status){
                printf("Error setting weights -- Err: %d\n", status);
                return EXIT_FAILURE;
        }

        layer1.forwardPass(&layer1);

        printf("Inputs:  %2.2f %2.2f %2.2f\n", 
                        inputs[0], inputs[1], inputs[2]);
        printf("Weights: %2.2f %2.2f %2.2f\n",  
                        weights[0], weights[1], weights[2]);
        printf("Output:  %2.4f\n", 
                        layer1.output[0]); 
        printf("Expect:  %2.4f\n", 
                        inputs[0] * weights[0]
                        + inputs[1] * weights[1] 
                        + inputs[2] * weights[2]);

        gmCleanupSummation(&layer1);
        gmCleanupUnit(&layer1);

        return EXIT_SUCCESS;
}
