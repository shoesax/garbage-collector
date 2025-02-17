#ifndef MARK_AND_SWEEP_H
#define MARK_AND_SWEEP_H

#include "object.h"

/**
 * @brief Marks all unreferenced space and memory and then sweeps it.
 *
 * @param[in] vm Pointer to vm who's memory will be marked and swept
 *
 *
 * @return       None
 */
void garbageCollector(VM* vm);

#endif //MARK_AND_SWEEP_H