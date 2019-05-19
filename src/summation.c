#include <stdlib.h>

#include "common.h"
#include "GreyMatter/unit.h"
#include "GreyMatter/summation.h"

/**
 */
struct weighted_summation_data {
        float *weights;
        float *dWeights;
};

/**
 */
static int forwardPassSummation(struct gm_unit *unit)
{
        int retCode = 0;
        int i = 0, j = 0;

        if (NULL == unit) {
                retCode = -E_NULLARG;
                goto _return;
        }

        if (NULL == unit->input || NULL == unit->output) {
                retCode = -E_UNINITIALISED;
                goto _return;
        }

        if (1 > unit->numInputs || 1 > unit->numOutputs) {
                retCode = -E_INVALIDSIZE;
                goto _return;
        }

        for (j = 0; j < unit->numOutputs; j++) {
                unit->output[j] = 0.f;
                for (i = 0; i < unit->numInputs; i++) {
                        unit->output[j] += *(unit->input[i]);
                }
        }

_return:
        return retCode;
}

/**
 */
static int forwardPassWeightedSummation(struct gm_unit *unit)
{
        int retCode = 0;
        int i = 0, j = 0;
        struct weighted_summation_data *model;

        if (NULL == unit) {
                retCode = -E_NULLARG;
                goto _return;
        }

        if (NULL == unit->input || NULL == unit->output || NULL == unit->model) {
                retCode = -E_UNINITIALISED;
                goto _return;
        }

        if (1 > unit->numInputs || 1 > unit->numOutputs) {
                retCode = -E_INVALIDSIZE;
                goto _return;
        }
        
        model = unit->model;

        for (j = 0; j < unit->numOutputs; j++) {
                unit->output[j] = 0.f;
                for (i = 0; i < unit->numInputs; i++) {
                        unit->output[j] += 
                                *(unit->input[i]) * model->weights[i + (j * unit->numInputs)];
                }
        }

_return:
        return retCode;
}

/**
 */
static int backwardPassSummation(struct gm_unit *unit)
{
        int retCode = 0;
        int i = 0, j = 0;

        if (NULL == unit) {
                retCode = -E_NULLARG;
                goto _return;
        }

        if (NULL == unit->input || NULL == unit->output) {
                retCode = -E_UNINITIALISED;
                goto _return;
        }

        if (1 > unit->numInputs || 1 > unit->numOutputs) {
                retCode = -E_INVALIDSIZE;
                goto _return;
        }

        for (i = 0; i < unit->numInputs; i++) {
                for (j = 0; j < unit->numOutputs; j++) {
                        *(unit->dInput[i]) += unit->dOutput[j];
                }
        }

_return:
        return retCode;
}

/**
 */
static int backwardPassWeightedSummation(struct gm_unit *unit)
{
        int retCode = 0;
        int i = 0, j = 0;
        struct weighted_summation_data *model;

        if (NULL == unit) {
                retCode = -E_NULLARG;
                goto _return;
        }

        if (NULL == unit->input || NULL == unit->output || NULL == unit->model) {
                retCode = -E_UNINITIALISED;
                goto _return;
        }

        if (1 > unit->numInputs || 1 > unit->numOutputs) {
                retCode = -E_INVALIDSIZE;
                goto _return;
        }
        
        model = unit->model;

        for (i = 0; i < unit->numInputs; i++) {
                for (j = 0; j < unit->numOutputs; j++) {
                        *(unit->dInput[i]) += 
                                unit->dOutput[j] * model->weights[i + (j * unit->numInputs)];
                        model->dWeights[i + (j * unit->numInputs)] = 
                                unit->dOutput[j] * *(unit->input[i]);
                }
        }

_return:
        return retCode;
}

/**
 */
int gmCreateSummation(struct gm_unit *unit)
{
        int retCode = 0;

        if (NULL == unit) {
                retCode = -E_NULLARG;
                goto _return;
        }

        if (NULL == unit->dInput || NULL == unit->input ||
                        NULL == unit->dOutput || NULL == unit->output) {
                retCode = -E_UNINITIALISED;
                goto _return;
        }

        if (NULL != unit->model || NULL != unit->forwardPass || NULL != unit->backwardPass) {
                retCode = -E_INITIALISED;
                goto _return;
        }

        unit->forwardPass = forwardPassSummation;
        unit->backwardPass = backwardPassSummation;

_return:
        return retCode;
}

/**
 */
int gmCreateWeightedSummation(struct gm_unit *unit)
{
        int retCode = 0;

        retCode = gmCreateSummation(unit);
        if (0 > retCode)
                goto _return;


_return:
        return retCode;
}
/**
 */
struct gm_unit * gmCreatePerceptron(int numInputs, int numOutputs, float (*actFunc)(float), float (*actDeriv)(float))
{
        struct gm_unit *unit = NULL;
        struct perceptron_data *model = NULL;

        if (1 > numInputs || 1 > numOutputs || NULL == actFunc || NULL == actDeriv)
                goto _return;

        unit = gmCreateUnit(numInputs, numOutputs);

        if (NULL == unit)
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
        return unit;
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
        
        for (i = 0; i < unit->numOutputs; i++) {
                for (j = 0; j < unit->numInputs; j++) {
                        idx = j + (i * unit->numInputs);
                        model->weights[idx] = weights[idx];
                }
        }
}
