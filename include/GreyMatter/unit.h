/**
 *
 *
 */

#ifndef GM_UNIT_H
#define GM_UNIT_H

#ifdef __cplusplus
extern C {
#endif

/**
 */
struct gm_unit {
        float ** inputs;
        float * outputs;
        void * model;
        void (*forwardPass)(struct gm_unit*);
        void (*backwardPass)(struct gm_unit*);
};

#ifdef __cplusplus
}
#endif

#endif
