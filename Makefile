# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 15:47:28 by ceatgie           #+#    #+#              #
#    Updated: 2022/11/22 13:29:16 by ceatgie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	main.c\
			Built-in/cd/ft_cd_error_manager.c\
			Built-in/cd/ft_cd.c\
			Built-in/cd/ft_change_directory.c\
			Built-in/cd/ft_convert_arg_to_path.c\
			Built-in/env/ft_env.c\
			Built-in/pwd/ft_pwd.c\
			Built-in/unset/ft_unset.c\
			Built-in/ft_is_built_in.c\
			Env/ft_change_env.c\
			Env/ft_create_env.c\
			Env/ft_create_temp_env.c\
			Env/ft_env_len.c\
			Env/ft_find_env.c\
			Env/ft_get_env_var.c\
			Env/ft_replace_env.c\
			Exec/ft_exec.c\
			Exec/ft_fd.c\
			Exec/ft_find_bin.c\
			Exec/ft_handle_pipe.c\
			Exec/ft_open_create.c\
			Exec/ft_pipes.c\
			Libft/ft_isalpha.c\
			Libft/ft_isdigit.c\
			Libft/ft_putchar_fd.c\
			Libft/ft_putendl_fd.c\
			Libft/ft_putstr_fd.c\
			Libft/ft_split.c\
			Libft/ft_strcmp.c\
			Libft/ft_strdup.c\
			Libft/ft_strjoin.c\
			Libft/ft_strncmp.c\
			Libft/ft_strndup.c\
			Minishell/ft_prompt.c\
			Minishell/minishell.c\
			Parsing/expand.c\
			Parsing/ft_cleanfile.c\
			Parsing/ft_echap.c\
			Parsing/ft_joindollar.c\
			Parsing/ft_quotes_else.c\
			Parsing/ft_quotes.c\
			Parsing/ft_splitargs.c\
			Parsing/parse.c\
			Redirect/ft_heredoc.c\
			Redirect/ft_redirections.c\
			Utils/ft_error.c\
			Utils/ft_exit.c\
			Utils/ft_free.c\
			Utils/ft_if_malloc_issue.c\
			Utils/ft_init.c\
			Utils/ft_libft.c\
			Utils/ft_lst_spe.c\
			Utils/ft_lst.c\
			Utils/ft_print_minishell.c\
			Utils/ft_push.c\
			Utils/ft_str.c\
			Utils/ft_verif.c\
			Utils/utils.c\
			Utils/utils2.c


OBJS= $(SRCS:.c=.o)

CC		=	gcc

CFLAGS	= -g3 -Iincludes
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