#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define EXIT_ERROR  (1)

int (*std_socket)(int domain, int type, int protocol);

static void *libc_handle = NULL;

void _mptcpmode_load()
{
    if (libc_handle != NULL)
        return;

    if (!(libc_handle = dlopen("libc.so", RTLD_LAZY))) {
        if (!(libc_handle = dlopen("libc.so.6", RTLD_LAZY))) {
            fprintf(stderr, "error loading libc!\n");
            exit (EXIT_ERROR);
        }
    }

    if (!(std_socket = dlsym(libc_handle, "socket"))) {
        fprintf(stderr, "socket() not found in libc!\n");
        exit (EXIT_ERROR);
    }
}

int socket(int domain, int type, int protocol)
{
    _mptcpmode_load();

    if (((IPPROTO_TCP == protocol) || (0 == protocol))
        && (SOCK_STREAM == type)) {

#ifdef DEBUG
        fprintf(stderr, "info: Set proto from %d to %d\n", protocol, IPPROTO_MPTCP);
#endif
        protocol = IPPROTO_MPTCP;
    }

    return (std_socket)(domain, type, protocol);
}
