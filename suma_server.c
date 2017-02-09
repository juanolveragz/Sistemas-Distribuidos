/*
 Implementa el procedimiento remoto
 */

#include "suma.h"

int *
suma_1_svc(intpair *argp, struct svc_req *rqstp)
{
	//Al vivir las variables locales en el stack result es estatica
	static int  result;

	/*
	 * insert server code here
	 */
//Se envia el resultado al cliente
printf("Server response to client...\n");
printf("parameters: %d, %d\n", argp->a, argp->b);
result = argp->a + argp->b;
printf("returning: %d\n", result);
return &result;
}
