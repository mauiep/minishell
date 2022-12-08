/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:37:42 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/08 01:58:18 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_else(char *buff, int fd, t_mini *data)
{
	t_lst	*tmp;

	tmp = ft_lstnew();
	if (!tmp)
		return (free(buff), free_lst(tmp), close(fd), -1);
	tmp->str = buff;
	if (mini_expand(tmp, data) < 0)
		return (free(buff), free_lst(tmp), close(fd), -1);
	tmp->str = ft_strpos(tmp->str);
	if (!tmp->str)
		return (free(buff), free_lst(tmp), close(fd), -1);
	write(fd, tmp->str, ft_strlen(tmp->str));
	write(fd, "\n", 1);
	ft_quadrafree(tmp->str, NULL, tmp, NULL);
	return (1);
}

/*
**
**	ft_heredoc est appele a l'utilisation de "<<" dans le minishell
**	A droite des chevrons se trouve la chaine de caracteres
**	qui fermera le heredoc
**	Readline ouvre un prompt et tout ce qui y sera envoye se verra
**	ecrit dans un tmpfile qui sera redirige vers STDIN
**	buff doit etre expand ($arg) et passee en positive puis ecris
**	dans le fd tmp
*/

int	ft_heredoc(t_lst *lst, t_mini *data, int fd)
{
	char				*buff;
	char				*end;

	if (ft_cleanfile(lst) < 0)
		return (-1);
	end = lst->str;
	while (42)
	{
		buff = readline("heredoc>");
		if (!buff)
		{
			return (ft_error("minishell: warning: here-document", RED, -1),
				ft_error(" delimited by end-of-file (wanted `", RED, -1),
				ft_putstr_fd(RED, 2),
				ft_putstr_fd(end, 2),
				ft_putstr_fd("')\n", 2),
				ft_putstr_fd(RESET, 2), -1);
		}
		if (ft_strcmp(buff, end) == 0)
			break ;
		if (ft_heredoc_else(buff, fd, data) == -1)
			return (-1);
	}
	return (free(buff), fd);
}

/*
**
**	Dans cette fonctino on va simplement remplacer,
** dans la ligne recuperee, les $variable
**	par leur valeur dans l'environnement.
**	Sauf si ils sont dans des simple quotes
**
*/

int	mini_expand(t_lst *tmp, t_mini *data)
{
	int		i;
	int		c;
	int		j;

	i = 0;
	c = 0;
	while (tmp->str && tmp->str[i])
	{
		j = 0;
		if (c == 0 && (tmp->str[i] == 39 || tmp->str[i] == 34))
			c = tmp->str[i];
		else if (c != 0 && tmp->str[i] == c)
			c = 0;
		else if (tmp->str[i] == '$' && c != 39
			&& tmp->str[i + 1] && tmp->str[i + 1] != ' ')
			j = ft_joindollar(tmp, i, data);
		if (j == -42)
			return (-1);
		i = i + j + 1;
	}
	return (1);
}
