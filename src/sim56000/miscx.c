/* Motorola SIM56000.EXE 6.3.0, miscx module, 0x45d280.
 * Original inactive external allocator release hook; other helpers are pending.
 */
#include "sim56000.h"

void dsp_free_ext(void *p)
{
    (void)p;
}
