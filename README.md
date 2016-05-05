# mptcp-mode
Program to enable/disable MPTCP for existing (binary) applications in Linux.

## description

This software enables/disables MPTCP for TCP applications without having to
recompile them. The enabling/disabling is done through a `LD_PRELOAD` which
replaces the `socket` system call with the following:

	strcpy(env_buff, getenv("LD_PRELOAD_MPTCPMODE"));

	if(strcmp("on", env_buff) == 0)
		enable = 1;

	if (((PF_INET == domain) || (PF_INET6 == domain))
	    && (SOCK_STREAM == type)) {

		fd = (std_socket)(domain, type, protocol);
		setsockopt(fd, SOL_TCP, MPTCP_ENABLED, &enable, sizeof(enable));

		return fd;
	}

Thus, using this software gives the same effect as if the application developer
would have implemented this socket option selection. The motivation for this
application is simply that it enables an easy "MPTCP-switch" for proprietary
closed-source software and for situations where you're just too lazy to change
the code...

## usage

Compile the software using `make` and use one of the two programs to turn on/off
MPTCP. For example:

	./mptcp-on wget http://www.google.com

or
	
	./mptcp-off wget http://www.google.com

