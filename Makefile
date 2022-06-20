CC = gcc

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC_N	=	dynarray.c ft_env.c ft_fd.c ft_pipes.c ft_sig.c \
			dynarray2.c ft_builtins.c ft_exec.c ft_mems.c ft_print.c \
			ft_str.c
SRC_A	= 

SRC		= ${SRC_N} ${SRC_A}
SRC_D = srcs
SRC_C = $(addprefix ${SRC_D}/, ${SRC})

INC = dynarray.h nikishell.h minishell.h
INC_D = includes
INC_H = $(addprefix ${INC_D}/, ${INC})

all: $(NAME)

$(NAME): ${INC_H} ${SRC_C}
	${CC} ${CFLAGS} ${SRC_C} srcs/co_main.c -I${INC_D} -o ${NAME} -lreadline

niki: ${INC_H} ${SRC_C}
	${CC} ${LDFLAGS} ${CPPFLAGS} ${CFLAGS} ${SRC_C} srcs/minishell.c -I${INC_D} -o ${NAME} -lreadline
adrien: ${INC_H} ${SRC_C}
	${CC} ${CFLAGS} ${SRC_C} srcs/co-main.c -I${INC_D} -o ${NAME} -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
