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
static int summationCreationCheck(struct gm_unit *unit)
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

_return:
        return retCode;

}

/**
 */
int gmCreateSummation(struct gm_unit *unit)
{
        int retCode = 0;

        retCode = summationCreationCheck(unit);
        if (0 > retCode) goto _return;

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
        struct weighted_summation_data *model = NULL;

        retCode = summationCreationCheck(unit);
        if (0 > retCode) goto _return;

        unit->model = malloc(sizeof(struct weighted_summation_data));
        if (NULL == unit->model) {
                retCode = -E_MEMORY;
                goto _return;
        }

        model = unit->model;
        model->weights = malloc(unit->numInputs * unit->numOutputs * sizeof(float));
        if (NULL == model->weights) {
                retCode = -E_MEMORY;
                goto _cleanup;
        }

        model->dWeights = malloc(unit->numInputs * unit->numOutputs * sizeof(float));
        if (NULL == model->dWeights) {
                retCode = -E_MEMORY;
                goto _cleanup;
        }

        unit->forwardPass = forwardPassWeightedSummation;
        unit->backwardPass = backwardPassWeightedSummation;

        goto _return;

_cleanup:
        gmCleanupSummation(unit);
_return:
        return retCode;
}

/**
 */
void gmCleanupSummation(struct gm_unit *unit)
{
        struct weighted_summation_data * model = NULL;
        if (NULL == unit)
                return;
        
        unit->forwardPass = NULL;
        unit->backwardPass = NULL;

        model = unit->model;
        if (NULL != model) {
                if (NULL != model->weights)
                        free(model->weights);
                if (NULL != model->dWeights)
                        free(model->dWeights);
                model->weights = NULL;
                model->dWeights = NULL;
                free(unit->model);
                unit->model = NULL;
        }
}

/**
 */
int gmSetSummationWeights(struct gm_unit * unit, float *weights)
{
        int retCode = 0;
        int i = 0, j = 0, idx = 0;
        struct weighted_summation_data * model;

        if (NULL == unit || NULL == weights) {
                retCode = -E_NULLARG;
                goto _return;
        }

        model = unit->model;
        if (NULL == model) {
                retCode = -E_UNINITIALISED;
                goto _return;
        }
        
        for (j = 0; j < unit->numOutputs; j++) {
                for (i = 0; i < unit->numInputs; i++) {
                        idx = i + (j * unit->numOutputs);
                        model->weights[idx] = weights[idx];
                }
        }
_return:
        return retCode;
}

/**
 */
int gmSetSummationWeight(struct gm_unit *unit, int inputIdx, int outputIdx, float weight)
{
        int retCode = 0;
        int idx = 0;
        struct weighted_summation_data * model;

        if (NULL == unit) {
                retCode = -E_NULLARG;
                goto _return;
        }

        model = unit->model;
        if (NULL == model) {
                retCode = -E_UNINITIALISED;
                goto _return;
        }
        
        idx = inputIdx + (outputIdx * unit->numOutputs);
        model->weights[idx] = weight;

_return:
        return retCode;
}
