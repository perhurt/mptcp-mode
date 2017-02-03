#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#ifndef MPTCP_ENABLED
#define MPTCP_ENABLED 42
#endif

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
    int enable = 0;
    int fd;
    char env_buff[256];

    _mptcpmode_load();

    strcpy(env_buff, getenv("LD_PRELOAD_MPTCPMODE"));

    if(strcmp("on", env_buff) == 0)
        enable = 1;

    if (((PF_INET == domain) || (PF_INET6 == domain))
        && (SOCK_STREAM == type)) {

        fd = (std_socket)(domain, type, protocol);
        setsockopt(fd, IPPROTO_TCP, MPTCP_ENABLED, &enable, sizeof(enable));

        return fd;
    }

    return (std_socket)(domain, type, protocol);
}
