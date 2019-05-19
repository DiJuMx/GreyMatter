/**
 *
 *
 */

#ifndef GM_UNIT_H
#define GM_UNIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration */
struct gm_unit;

/** Type definition for all unit agnostic functions
 *
 */
typedef int (*procFnc)(struct gm_unit*);

/**
 */
struct gm_unit {
        int     numInputs;      /**< */
        int     numOutputs;     /**< */
        float   **input;        /**< */
        float   **dInput;       /**< */
        float   *output;        /**< */
        float   *dOutput;       /**< */
        void    *model;         /**< */
        procFnc forwardPass;    /**< */
        procFnc backwardPass;   /**< */
};


/** \addtogroup VarArgs Variadic Argument Keys
 * @{
 */
#define ARG_DONE        0       /**< Must be the final argument. Indicates end of argument list */

/** @} */

/** \addtogroup ErrCodes Error Codes and Return Values
 *
 * Success is always 0. 
 * @{
 */
#define E_NULLARG       1       /**< A required argument was NULL */
#define E_UNKNOWNARG    2       /**< A variadic argument is unknown */
#define E_INVALIDARG    3       /**< A variadic argument is invalid */
#define E_INVALIDSIZE   4       /**< A supplied size is invalid */
#define E_MEMORY        5       /**< There was an error allocating space */

/** @} */

int gmCreateUnit(struct gm_unit *unit, int numInputs, int numOutputs);

void gmCleanupUnit(struct gm_unit *unit);

#ifdef __cplusplus
}
#endif

#endif
