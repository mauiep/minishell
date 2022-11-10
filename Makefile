# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admaupie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 15:45:17 by admaupie          #+#    #+#              #
#    Updated: 2022/11/09 15:45:21 by admaupie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -static-libasan

SRC_N	= dynarray.c ft_env.c ft_fd.c ft_pipes.c ft_sig.c \
			dynarray2.c ft_builtins.c ft_exec.c ft_mems.c ft_print.c \
			ft_str.c ft_redirections.c ft_prompt.c ft_files.c ft_minishell.c
SRC_A	= *

SRC_NN	= $(addprefix ${SRC_D}/, ${SRC_N})
SRC_AA	= $(addprefix ${SRC_AD}/, ${SRC_A})
SRC		= ${SRC_NN} ${SRC_AA}
SRC_D	= srcs
SRC_AD	= srcs_a
SRC_C	= $(addprefix ${SRC_D}/, ${SRC})

INC		= minishell.h
INC_D	= includes
INC_H	= $(addprefix ${INC_D}/, ${INC})

all: $(NAME)

$(NAME): ${INC_H} ${SRC}
	${CC} ${CFLAGS} niki_main.c ${SRC} -I${INC_D} -o ${NAME} -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
