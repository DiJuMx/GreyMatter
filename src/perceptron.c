#include <stdlib.h>

#include "common.h"
#include "GreyMatter/unit.h"

struct perceptron_data {
        float * weights;
        float (*act_func)(float);
        float (*deriv_func)(float);
};

static void forwardPassPerceptron(struct gm_unit * unit)
{
        int i=0, j=0;
        float (*activation)(float) = ((struct perceptron_data *) unit->model)->act_func;
        float *weights =((struct perceptron_data*) unit->model)->weights;

        if (NULL == activation || NULL == weights)
                return;

        for (i = 0; i < unit->numOutputs; i++) {
                unit->output[i] = 0.f;
                for (j = 0; j < unit->numInputs; j++) {
                     unit->output[i] += *(unit->input[j]) * weights[j + (i*unit->numInputs)];
                }
                unit->output[i] = (*activation)(unit->output[i]);
        }
}

int gmCreatePerceptron(struct gm_unit * unit, float (*actFunc)(float), float (*actDeriv)(float))
{
        int status = -1;
        struct perceptron_data *model = NULL;

        if (NULL == actFunc || NULL == actDeriv || NULL == unit)
                goto _return;

        unit->forwardPass = forwardPassPerceptron;

        unit->model = malloc(1 * sizeof(struct perceptron_data));
        if (NULL == unit->model)
                goto _return;

        model = unit->model;
        model->act_func = actFunc;
        model->deriv_func = actDeriv;

        model->weights = malloc(unit->numInputs * unit->numOutputs * sizeof(float));
        if (NULL == model->weights)
                goto _cleanup_model;

        status = 0;
        goto _return;

_cleanup_model:
        free(unit->model);
_return:
        return status;
}

void gmDestroyPerceptron(struct gm_unit * unit)
{
        if (NULL != unit->model)
                free(unit->model);
        if (NULL != unit)
                free(unit);
}

