#include <stdlib.h>

#include "common.h"
#include "GreyMatter/unit.h"

/**
 */
int gmCreateUnit(struct gm_unit *unit, int numInputs, int numOutputs)
{
        int retCode = 0;
        int fail = 0;

        if (NULL == unit) {
                retCode = -E_NULLARG;
                goto _return;
        }

        /* Ensure we have NULL pointers */
        unit->input = NULL;
        unit->dInput = NULL;
        unit->output = NULL;
        unit->dOutput = NULL;
        unit->model = NULL;
        
        if (0 > numInputs || 1 > numOutputs) {
                retCode = -E_INVALIDSIZE;
                goto _return;
        }

        /* Copy size to structure */
        unit->numInputs = numInputs;
        unit->numOutputs = numOutputs;

        if (numInputs > 0){
                unit->input = malloc(unit->numInputs * sizeof(float*));
                fail |= (NULL == unit->input);
                unit->dInput = malloc(unit->numInputs * sizeof(float*));
                fail |= (NULL == unit->dInput);
        }
        unit->output = malloc(unit->numOutputs * sizeof(float));
        fail |= (NULL == unit->output);
        unit->dOutput = malloc(unit->numOutputs * sizeof(float));
        fail |= (NULL == unit->dOutput);

        /* If any of the allocations fail, cleanup */
        if (fail) {
                gmCleanupUnit(unit);
                retCode = -E_MEMORY;
        }

_return:
        return retCode;
}

/**
 */
void gmCleanupUnit(struct gm_unit * unit)
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
        }
}

