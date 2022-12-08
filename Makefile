# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 15:47:28 by ceatgie           #+#    #+#              #
#    Updated: 2022/12/08 05:15:24 by ceatgie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	main.c\
			Built-in/cd/ft_add_home_path.c\
			Built-in/cd/ft_cd_check_if_arg_is_dash.c\
			Built-in/cd/ft_cd_error_manager.c\
			Built-in/cd/ft_cd.c\
			Built-in/cd/ft_change_directory.c\
			Built-in/cd/ft_convert_arg_to_path.c\
			Built-in/echo/ft_echo.c\
			Built-in/env/ft_env.c\
			Built-in/exit/ft_exit.c\
			Built-in/export/ft_add_env_var.c\
			Built-in/export/ft_check_export_arg.c\
			Built-in/export/ft_export.c\
			Built-in/export/ft_sort_and_print_env.c\
			Built-in/pwd/ft_pwd.c\
			Built-in/unset/ft_check_unset_arg.c\
			Built-in/unset/ft_realloc_env.c\
			Built-in/unset/ft_unset.c\
			Built-in/ft_is_built_in.c\
			Env/ft_change_env.c\
			Env/ft_create_env.c\
			Env/ft_create_temp_env.c\
			Env/ft_env_len.c\
			Env/ft_find_env.c\
			Env/ft_get_env_var.c\
			Exec/ft_exec_else.c\
			Exec/ft_exec.c\
			Exec/ft_fd.c\
			Exec/ft_find_bin.c\
			Exec/ft_handle_pipe.c\
			Exec/ft_signals.c\
			Exec/ft_wait_procs.c\
			Exec/ft_exec_error.c\
			Libft/ft_isalpha.c\
			Libft/ft_isdigit.c\
			Libft/ft_itoa.c\
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
			Minishell/launch_minishell.c\
			Parsing/expand.c\
			Parsing/ft_check_redir.c\
			Parsing/ft_cleanfile.c\
			Parsing/ft_echap.c\
			Parsing/ft_joindollar.c\
			Parsing/ft_quotes_else.c\
			Parsing/ft_quotes.c\
			Parsing/ft_splitargs.c\
			Parsing/ft_wrong_syntax_newline_check.c\
			Parsing/ft_wrong_syntax_redir_check.c\
			Parsing/parse.c\
			Redirect/ft_for_token.c\
			Redirect/ft_heredoc.c\
			Redirect/ft_create_heredoc.c\
			Redirect/ft_open_create.c\
			Redirect/ft_pipes_utils.c\
			Redirect/ft_pipes.c\
			Redirect/ft_redirections.c\
			Utils/ft_error_msg.c\
			Utils/ft_error_token.c\
			Utils/ft_error.c\
			Utils/ft_free.c\
			Utils/ft_if_malloc_issue.c\
			Utils/ft_init.c\
			Utils/ft_is_inside_quote.c\
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

CFLAGS	= -g3 -Iincludes -Wall -Wextra -Werror

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