/**
 *
 */
#ifndef GREYMATTER_SUMMATION_H
#define GREYMATTER_SUMMATION_H

#include "GreyMatter/unit.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int gmCreateSummation(struct gm_unit *unit);
int gmCreateWeightedSummation(struct gm_unit *unit);

void gmCleanupSummation(struct gm_unit *unit);

int gmSetSummationWeights(struct gm_unit *unit, float *weights);
int gmSetSummationWeight(struct gm_unit *unit, int inputIdx, int outputIdx, float weight);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GREYMATTER_NEAT_H */
