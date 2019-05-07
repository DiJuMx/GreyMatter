/**
 *
 */
#ifndef GREYMATTER_PERCEPTRON_H
#define GREYMATTER_PERCEPTRON_H

#include "GreyMatter/unit.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 */
int gmCreatePerceptron(struct gm_unit * unit, float (*actFunc)(float), float (*actDeriv)(float));

/**
 */
void gmDestroyPerceptron(struct gm_unit * unit);

/**
 */
void gmSetPerceptronWeights(struct gm_unit * unit, float *weights);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GREYMATTER_NEAT_H */
