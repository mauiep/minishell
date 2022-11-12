# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 15:47:28 by ceatgie           #+#    #+#              #
#    Updated: 2022/11/12 01:19:46 by ceatgie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	main.c\
			Adrien/ft_cleanfile.c\
			Adrien/ft_exec.c\
			Adrien/ft_fd.c\
			Adrien/ft_files.c\
			Adrien/ft_joindollar.c\
			Adrien/ft_lst_spe.c\
			Adrien/ft_lst.c\
			Adrien/ft_minishell_adrien.c\
			Adrien/ft_pipes.c\
			Adrien/ft_push.c\
			Adrien/ft_quotes.c\
			Adrien/ft_redirections.c\
			Adrien/ft_splitargs.c\
			Adrien/ft_str.c\
			Adrien/ft_verif.c\
			Adrien/parse.c\
			Adrien/utils.c\
			Adrien/utils2.c\
			Built-in/pwd/ft_pwd.c\
			Built-in/ft_is_built_in.c\
			Env/ft_change_env.c\
			Env/ft_create_env.c\
			Env/ft_create_temp_env.c\
			Env/ft_env_len.c\
			Env/ft_find_env.c\
			Env/ft_get_env_var.c\
			Env/ft_replace_env.c\
			Libft/ft_bzero.c\
			Libft/ft_calloc.c\
			Libft/ft_isalpha.c\
			Libft/ft_isdigit.c\
			Libft/ft_memset.c\
			Libft/ft_putchar_fd.c\
			Libft/ft_putendl_fd.c\
			Libft/ft_putstr_fd.c\
			Libft/ft_split.c\
			Libft/ft_strcmp.c\
			Libft/ft_strdup.c\
			Libft/ft_strjoin.c\
			Libft/ft_strlen.c\
			Libft/ft_strncmp.c\
			Libft/ft_strndup.c\
			Minishell/ft_prompt.c\
			Minishell/minishell.c\
			Utils/ft_error.c\
			Utils/ft_exit.c\
			Utils/ft_free.c\
			Utils/ft_if_malloc_issue.c\
			Utils/ft_init.c\
			Utils/ft_print_minishell.c\


OBJS= $(SRCS:.c=.o)

CC		=	gcc

CFLAGS	= -g3
.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all : ${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -lreadline

clean:
			rm -rf ${OBJS}

fclean:		clean
			rm -rf ${NAME}

re:			fclean all

.PHONY:	all clean fclean re