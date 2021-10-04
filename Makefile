# Makefile template for shared library

CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  -ldl # linking flags
RM = rm -f  # rm command
TARGET_LIB = libmptcpmode.so # target lib
MPTCPRUN = mptcp-run
MPTCPRUNSRC = mptcp-run.in
SRCS = mptcp_mode.c
OBJS = $(SRCS:.c=.o)
#
.PHONY: all
all: ${TARGET_LIB} ${MPTCPRUN}

$(MPTCPRUN):
	cp ${MPTCPRUNSRC} ${MPTCPRUN}
	chmod +x ${MPTCPRUN}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

#include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${MPTCPRUN} ${OBJS} $(SRCS:.c=.d)

