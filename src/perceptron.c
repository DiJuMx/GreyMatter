#include <stdlib.h>
#include "GreyMatter/unit.h"
#include "common.h"

struct perceptron_data {
        float * weights;
        float (*act_func)(float);
};

struct gm_unit * gmCreatePerceptron(int numInputs, int numOutputs)
{
        UNUSED(numInputs);
        UNUSED(numOutputs);

        return NULL;
}

void gmPerceptronSetActivationFunction(struct gm_unit * unit, float (*func)(float))
{
        UNUSED(unit);
        UNUSED(func);

}
