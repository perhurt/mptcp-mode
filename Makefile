# Makefile template for shared library

CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  -ldl # linking flags
RM = rm -f  # rm command
TARGET_LIB = libmptcpmode.so # target lib
MPTCPON = mptcp-on
MPTCPOFF = mptcp-off
MPTCPONSRC = mptcp-on.in
MPTCPOFFSRC = mptcp-off.in
SRCS = mptcp_mode.c
OBJS = $(SRCS:.c=.o)
#
.PHONY: all
all: ${TARGET_LIB} ${MPTCPON} ${MPTCPOFF}

$(MPTCPON):
	cp ${MPTCPONSRC} ${MPTCPON}
	chmod +x ${MPTCPON}

$(MPTCPOFF):
	cp ${MPTCPOFFSRC} ${MPTCPOFF}
	chmod +x ${MPTCPOFF}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

#include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${MPTCPON} ${MPTCPOFF} ${OBJS} $(SRCS:.c=.d)

