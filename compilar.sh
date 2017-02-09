#!/bin/sh

echo Se esta compilando

gcc -g -DRPC_SVC_FG -c -o bitacora_clnt.o bitacora_clnt.c
gcc -g -DRPC_SVC_FG -c -o bitacora_client.o bitacora_client.c
gcc -g -DRPC_SVC_FG -o bitacora_client bitacora_clnt.o bitacora_client.o
gcc -g -DRPC_SVC_FG -c -o bitacora_svc.o bitacora_svc.c
gcc -g -DRPC_SVC_FG -c -o bitacora_server.o bitacora_server.c
gcc -g -DRPC_SVC_FG -o bitacora_server bitacora_svc.o bitacora_server.o
