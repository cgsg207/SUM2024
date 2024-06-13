/* FILE NAME  : rndgrid.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : Restart primitives.
 */

#include "def.h"
#include "rnd.h"

/* Grid topology reoresentation type */
typedef struct tagan5GRID
{
  INT W, H;     /* Grid size (in vertices) */
  an5VERTEX *V; /* Array (2D) of vertex */
} an5GRID;

/* End of 'rndgrid.c' file */