#include <stdlib.h>

#include "common.h"
#include "GreyMatter/unit.h"


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

        goto _return;

_cleanup_input:
        free(unit->input);
_cleanup_unit:
        free(unit);
_return:
        return unit;
}

void gmDestroyUnit(struct gm_unit * unit)
{
        if (NULL != unit) {
                if (NULL != unit->input)
                        free(unit->input);
                if (NULL != unit->output)
                        free(unit->output);
                free(unit);
        }
}

