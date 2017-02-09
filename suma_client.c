/*
 Crea al cliente gracias a la función clnt_create
 */
#include <stdio.h>
#include "suma.h"

//Recibe argumentos del main
void
suma_prog_1(char *host, int a, int b)
{
	CLIENT *clnt;
	int  *result_1;
	intpair  suma_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, SUMA_PROG, SUMA_VERS, "udp");//Parametros que crean el cliente
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
        suma_1_arg.a = a;
        suma_1_arg.b = b;//Datos que se suman
	result_1 = suma_1(&suma_1_arg, clnt);//suma los valores
	 if (result_1 == (int *) NULL) {
         clnt_perror (clnt, "call failed");
      } else {
        printf("result = %d\n", *result_1);//Imprime el resultado
}
#ifndef	DEBUG
	clnt_destroy (clnt);//termina el proceso del cliente
#endif	 /* DEBUG */
}

//esta función toma la dirección del servidor y los datos a sumar
int
main(int argc, char *argv[]) {
        char *host;
        int a, b;
        if (argc != 4) {// las condicipnes se encargan de que los datos sean del tipo correcto
            printf ("usage: %s server_host num1 num2\n", argv[0]);
            exit(1);
        }
        host = argv[1];
        if ((a = atoi(argv[2])) == 0 && *argv[2] != '0') {
            fprintf(stderr, "invalid value: %s\n", argv[2]);
            exit(1);
        }
        if ((b = atoi(argv[3])) == 0 && *argv[3] != '0') {
            fprintf(stderr, "invalid value: %s\n", argv[3]);
            exit(1);
        }
        suma_prog_1(host, a, b);//se comprueba que los datos sean correctos
}
