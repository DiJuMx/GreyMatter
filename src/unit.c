#include <stdlib.h>

#include "common.h"
#include "GreyMatter/unit.h"

float BIAS_F = 1.f;

/**
 */
struct gm_unit * gmCreateUnit(int numInputs, int numOutputs)
{
        struct gm_unit * unit = NULL;

        if (0 > numInputs || 1 > numOutputs)
                goto _return;
        
        unit = malloc(1 * sizeof(*unit));

        if (NULL == unit)
                goto _return;

        /* One is added to take into account the presence of the bias */
        unit->numInputs = numInputs + 1;
        unit->numOutputs = numOutputs;

        unit->input = malloc(unit->numInputs * sizeof(float*));
        if (NULL == unit->input)
                goto _cleanup_unit;

        unit->output = malloc(unit->numOutputs * sizeof(float));
        if (NULL == unit->output)
                goto _cleanup_input;

        unit->dInput = malloc(unit->numInputs * sizeof(float*));
        if (NULL == unit->dInput)
                goto _cleanup_output;

        unit->dOutput = malloc(unit->numOutputs * sizeof(float));
        if (NULL == unit->output)
                goto _cleanup_dInput;

        unit->dInput = malloc(unit->numInputs * sizeof(float));

        unit->input[0] = &BIAS_F;

        goto _return;

_cleanup_dInput:
        free(unit->dInput);
        unit->dInput = NULL;
_cleanup_output:
        free(unit->output);
        unit->output = NULL;
_cleanup_input:
        free(unit->input);
        unit->input = NULL;
_cleanup_unit:
        free(unit);
        unit = NULL;
_return:
        return unit;
}

/**
 */
void gmDestroyUnit(struct gm_unit * unit)
{
        if (NULL != unit) {
                if (NULL != unit->input) {
                        free(unit->input);
                        unit->input = NULL;
                }
                if (NULL != unit->output) {
                        free(unit->output);
                        unit->output = NULL;
                }
                if (NULL != unit->dInput) {
                        free(unit->dInput);
                        unit->dInput = NULL;
                }
                if (NULL != unit->dOutput) {
                        free(unit->dOutput);
                        unit->dOutput = NULL;
                }
                free(unit);
        }
}

