//skeleton del servidor

#include "suma.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

//parametros generales para definir un identificador
#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

//skeleton del servidor que Implementa sumar
static void
suma_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		intpair suma_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

//todos los procedimientos remotos
	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

//procedimiento de suma
	case SUMA:
		_xdr_argument = (xdrproc_t) xdr_intpair;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) suma_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	//unmarshalling
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

//implementa el codigo principal y se registra el servicio
int
main (int argc, char **argv)
{
	register SVCXPRT *transp; //registro

	pmap_unset (SUMA_PROG, SUMA_VERS);// borra la entrada para SUMA_PROG de las tablas
// rutina para obtener un identificador de protocolo donde se cre un socket
	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, SUMA_PROG, SUMA_VERS, suma_prog_1, IPPROTO_UDP)) {
		//se especifica un numero de protocolo distinto de cero en svc_register
		fprintf (stderr, "%s", "unable to register (SUMA_PROG, SUMA_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	//Rutina para obtener un identificador de protocolo de datagramas de usuario
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, SUMA_PROG, SUMA_VERS, suma_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (SUMA_PROG, SUMA_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
