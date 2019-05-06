#include <stdlib.h>

#include "common.h"
#include "GreyMatter/unit.h"

struct perceptron_data {
        float * weights;
        float * dWeights;
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

static void backwardPassPerceptron(struct gm_unit * unit)
{
        int i=0, j=0;
        float (*derivative)(float) = ((struct perceptron_data *) unit->model)->deriv_func;
        float *weights =((struct perceptron_data*) unit->model)->weights;

        if (NULL == derivative || NULL == weights)
                return;

        for (i = 0; i < unit->numInputs; i++) {
                unit->dInput[i] = 0.f;
                for (j = 0; j < unit->numOutputs; j++) {
                        unit->dInput[i] += *(unit->dOutput[j]) * weights[i + (j*unit->numInputs)];
                }
        }
}

//static void weightUpdatePerceptron(struct gm_unit * unit, int updateMethod);

int gmCreatePerceptron(struct gm_unit * unit, float (*actFunc)(float), float (*actDeriv)(float))
{
        int status = -1;
        struct perceptron_data *model = NULL;

        if (NULL == actFunc || NULL == actDeriv || NULL == unit)
                goto _return;

        unit->forwardPass = &forwardPassPerceptron;
        unit->backwardPass = &backwardPassPerceptron;

        unit->model = malloc(1 * sizeof(struct perceptron_data));
        if (NULL == unit->model)
                goto _return;

        model = unit->model;
        model->act_func = actFunc;
        model->deriv_func = actDeriv;

        model->weights = malloc(unit->numInputs * unit->numOutputs * sizeof(float));
        if (NULL == model->weights)
                goto _cleanup_model;

        model->dWeights = malloc(unit->numInputs * unit->numOutputs * sizeof(float));
        if (NULL == model->dWeights)
                goto _cleanup_weights;



        status = 0;
        goto _return;

_cleanup_weights:
        free(model->weights);
        model->weights = NULL;
_cleanup_model:
        free(unit->model);
        unit->model = NULL;
_return:
        return status;
}

void gmDestroyPerceptron(struct gm_unit * unit)
{
        if (NULL != unit) {
                if (NULL != unit->model) {
                        free(unit->model);
                        unit->model = NULL;
                }
                gmDestroyUnit(unit);
        }
}

