#include <stdio.h>
#include "vsip.h"

#define N 4            /* length */

int main()
{
  double data[N]; /* a user-created data space */
  int i;
  vsip_vview_d* a;
  vsip_vview_d* x;

  vsip_init((void *)0);
  a = vsip_vbind_d(vsip_blockbind_d(data,N, VSIP_MEM_NONE),0,1,N);
  x = vsip_vcreate_d(N, VSIP_MEM_NONE);
  vsip_vramp_d(0.0, 1.0, x);
  /* admit the user block with no update */
  vsip_blockadmit_d(vsip_vgetblock_d(a),VSIP_FALSE);
  /*compute the 10^x value */
  vsip_vexp10_d(x, a);
  /* release the user block with update */
  vsip_blockrelease_d(vsip_vgetblock_d(a),VSIP_TRUE);
  /*print it */
  for(i=0; i<N; i++)
    printf("%f ",data[i]);
  printf("\n");
  /*destroy the vector views and any associated blocks */
  vsip_blockdestroy_d(vsip_vdestroy_d(x));
  vsip_blockdestroy_d(vsip_vdestroy_d(a));
  vsip_finalize((void *)0);
  return 0;
}
/* output */
/* 1.000000 10.000000 100.000000 1000.000000 */
