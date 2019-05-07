#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "GreyMatter/unit.h"
#include "GreyMatter/perceptron.h"

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
        float inputs[] = {1.f, 1.f};

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

        gmSetPerceptronWeights(layer1, weights);

        layer1->input[1] = &inputs[0];
        layer1->input[2] = &inputs[1];

        layer1->forwardPass(layer1);

        printf("Weights: %2.2f %2.2f %2.2f\n",  
                        weights[0], weights[1], weights[2]);
        printf("Inputs:  %2.2f %2.2f %2.2f\n",  
                        *(layer1->input[0]), *(layer1->input[1]), *(layer1->input[2]));
        
        printf("Output:  %2.8f\n",
                       layer1->output[0]); 

        printf("Expect:  %2.8f\n",
                        tanhf(
                                1.0f * weights[0]
                                + inputs[0] * weights[1]
                                + inputs[1] * weights[2] ));

        return EXIT_SUCCESS;
}
