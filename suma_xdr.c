/*
LLeva a cabo la serializacion de los datos.
 */

#include "suma.h"

bool_t
xdr_intpair (XDR *xdrs, intpair *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->a))//Serializacion de el primer entero
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->b))//Serializacion de el segundo entero
		 return FALSE;
	return TRUE;
}
