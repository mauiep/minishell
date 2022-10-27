/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:44:12 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/26 18:48:43 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "dynarray.h"
# define SIMPLE_QUOTE 39

typedef struct s_lst
{
	char			*str;
	int				token;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

//main.c
int		get_word(char *buffer, t_lst *new);
int		push_word(t_lst *lst, char *buffer);
int		parse(char *line_buffer, t_dynarray *darr);

//ft_lst.c
int		free_lst(t_lst *src);
void	ft_printlst(t_lst *a);
void	push_lst(t_lst *new, t_lst *lst);
t_lst	*ft_lstnew(void);
int		lst_len(t_lst *lst);
//ft_lst_spe.c
int		push_first_lst(t_lst *new, t_lst *lst);
t_lst	*pick_the_lst(t_lst *last);
t_lst	*first_lst(t_lst *lst);

//ft_libft.c
int		ft_strlen(char *str);
char	*ft_strndup(const char *src, int n);
int		ft_strcmp(const char *s1, const char *s2);

//utils.c
int		print_err(int err);
int		which_redirect(char *str);
int		is_sep(char c);

//ft_push.c
int		push_word(t_lst *lst, char *buffer);
int		push_sep(t_lst *lst, char *buffer);

//ft_joindollar.c
int		ft_strjoindollar(t_lst *l, char *var, int k, int dollar);
int		ft_replacedollar(t_lst *l, int k, int c, t_dynarray *darr);

//ft_verif.c
int		ft_verif(t_lst *lst);
int		recover_args(t_lst *last, char *buffer);
int		last_redirect(t_lst *lst); // lui donner le maillon > pour savoir si il ya encore des > ou >> apres
// n'existent pas
int		has_pipe(t_lst *l);
int		has_redirect(t_lst *l);

//ft_splitargs.c
char	**ft_splitargs(t_lst *lst);
int		spe_lenword(char *str);
int		remove_quotes(char **tab);

#endif
