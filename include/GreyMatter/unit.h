/**
 *
 *
 */

#ifndef GM_UNIT_H
#define GM_UNIT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 */
struct gm_unit {
        int     numInputs;
        int     numOutputs;
        float   **input;
        float   *dInput;
        float   *output;
        float   **dOutput;
        void    *model;
        void    (*forwardPass)(struct gm_unit*);
        void    (*backwardPass)(struct gm_unit*);
};

/**
 */
struct gm_unit * gmCreateUnit(int numInputs, int numOutputs);

/**
 */
void gmDestroyUnit(struct gm_unit * unit);

#ifdef __cplusplus
}
#endif

#endif
