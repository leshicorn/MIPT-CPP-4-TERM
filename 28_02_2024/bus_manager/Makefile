SRC_DIR=src
OBJ_DIR=obj
SRCS=$(shell find ${SRC_DIR} -name "*.cpp")
OBJS=$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.cpp=.o))
CC=g++
AR=ar
CFLAGS=-Wall -Wextra -Werror -I ./inc
NAME=libft.a

.PHONY: fclean clean all

all: ${OBJS}
	${AR} -rc ${NAME} ${OBJS}

${OBJS}: ${SRCS}
	mkdir -p $(@D)
	${CC} ${CFLAGS} -c -o $@ ${patsubst ${OBJ_DIR}/%,${SRC_DIR}/%,${@:.o=.cpp}}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all