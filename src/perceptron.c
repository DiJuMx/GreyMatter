#include <stdlib.h>

#include "common.h"
#include "GreyMatter/unit.h"

/**
 */
struct perceptron_data {
        float *summation;
        float *weights;
        float *dWeights;
        float (*act_func)(float);
        float (*deriv_func)(float);
};

/**
 */
static void forwardPassPerceptron(struct gm_unit * unit)
{
        int i=0, j=0;
        struct perceptron_data * model = NULL;
        float (*activation)(float) = NULL;
        float *weights = NULL;
        
        if (NULL == unit)
                return;

        model = unit->model;
        if (NULL == model)
                return;

        activation = model->act_func;
        weights = model->weights;
        if (NULL == activation || NULL == weights)
                return;

        for (i = 0; i < unit->numOutputs; i++) {
                model->summation[i] = 0.f;
                for (j = 0; j < unit->numInputs; j++) {
                        model->summation[i] += *(unit->input[j]) * weights[j + (i * unit->numInputs)];
                }
                unit->output[i] = (*activation)(model->summation[i]);
                unit->dOutput[i] = 0.f;
        }
}

/**
 */
static void backwardPassPerceptron(struct gm_unit * unit)
{
        int i=0, j=0;
        float temp = 0.f;
        struct perceptron_data * model = NULL;
        float (*derivative)(float) = NULL;
        float *weights = NULL;
        
        if (NULL == unit)
                return;

        model = unit->model;
        if (NULL == model)
                return;

        derivative = model->deriv_func;
        weights = model->weights;
        if (NULL == derivative || NULL == weights)
                return;

        for (i = 0; i < unit->numOutputs; i++) {
                temp = (*derivative)(model->summation[i]) * unit->dOutput[i];
                for (j = 0; j < unit->numInputs; j++) {
                        *(unit->dInput[j]) += temp * model->weights[j + (i * unit->numInputs)];
                        model->dWeights[j + (i * unit->numInputs)] = temp * *(unit->input[j]);
                }
        }
}

//static void weightUpdatePerceptron(struct gm_unit * unit, int updateMethod);

/**
 */
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

        model->summation = malloc(unit->numOutputs * sizeof(float));
        if (NULL == model->summation)
                goto _cleanup_dWeights;

        status = 0;
        goto _return;
_cleanup_dWeights:
        free(model->dWeights);
        model->dWeights = NULL;
_cleanup_weights:
        free(model->weights);
        model->weights = NULL;
_cleanup_model:
        free(unit->model);
        unit->model = NULL;
_return:
        return status;
}

/**
 */
void gmDestroyPerceptron(struct gm_unit * unit)
{
        struct perceptron_data * model = NULL;
        if (NULL != unit) {
                if (NULL != (model = unit->model)) {
                        if (NULL != model->summation) {
                                free(model->summation);
                                model->summation = NULL;
                        }
                        if (NULL != model->dWeights) {
                                free(model->dWeights);
                                model->dWeights = NULL;
                        }
                        if (NULL != model->weights) {
                                free(model->weights);
                                model->weights = NULL;
                        }
                        free(unit->model);
                        unit->model = NULL;
                }
                gmDestroyUnit(unit);
        }
}

/**
 */
void gmSetPerceptronWeights(struct gm_unit * unit, float *weights)
{
        int i = 0, j = 0, idx = 0;
        struct perceptron_data * model;
        if (NULL == unit || NULL == weights)
            return;
        
        model = unit->model;
        if (NULL == model)
            return;
        
        for (i = 0; i < input->numOutputs; i++) {
                for (j = 0; j < input->numInputs; j++) {
                        idx = j + (i * unit->numInputs);
                        model->weights[idx] = weights[idx];
                }
        }
}
