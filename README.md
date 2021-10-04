# mptcp-mode
Program to enable MPTCP for existing (binary) applications in Linux.

## description

This software enables MPTCP for TCP applications without having to
recompile them. This is done through a `LD_PRELOAD` which
changes the protocol in `socket` calls before passing them on to the actual
libc.

Thus, using this software gives the same effect as if the application developer
would have selected MPTCP themselves. The motivation for this
application is simply that it enables an easy "MPTCP-switch" for proprietary
closed-source software and for situations where you're just too lazy to change
the code...

## usage

Compile the software using `make` and use this program to turn on
MPTCP. For example:

	./mptcp-run wget http://www.google.com
