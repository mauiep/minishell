/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:37:42 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/18 14:36:33 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	ft_heredoc est appele a l'utilisation de "<<" dans le minishell
	A droite des chevrons se trouve la chaine de caracteres
	qui fermera le heredoc
	readline ouvre un prompt et tout ce qui y sera envoye se verra ecrit dans un
	tmpfile qui sera redirige vers STDIN

	buff doit etre expand ($arg) et passee en positive puis ecris dans le fd tmp

*/

int	ft_heredoc(char	*end, t_mini *data)
{
	char	*buff;
	int		fd;
	t_lst	*tmp;

	fd = open("temp", O_WRONLY | O_TRUNC | O_CREAT, 0755); //open("/.tmp_file", __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);//open("./tmp_file", O_RDWR | O_TRUNC | O_CREAT);//open("/.tmpheredoc", __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (printf("open fail\n"), -1);
	while (42)
	{
		buff = readline("heredoc>");// Affiche un prompt a l'ecran, l'utilisateur peut ecrire
		if (ft_strcmp(buff, end) == 0) // Si la str return par readline correspond a notre limit string on sort et return le fd
			break ;
		tmp = ft_lstnew();// Sinon on cree un maillon de liste pour effectuer l'expand dessus
		if (!tmp)
			return (free(buff), close(fd), -1);// Si l'allocation echoue on close le fd, free le readline
		tmp->str = buff;
		if (mini_expand(tmp, data) < 0) // On expand les $arg, ceux ci sont mis en negatif
			return (free(buff), free(tmp), close(fd), -1);
		tmp->str = ft_strpos(tmp->str); // On repasse en positif les caracteres
		if (!tmp->str)
			return (free(buff), free(tmp), close(fd), -1);
		write(fd, tmp->str, ft_strlen(tmp->str));
		write(fd, "\n", 1);
		// ft putstr_fd_endl    
		ft_quadrafree(tmp->str, NULL, tmp, NULL);
	}
	return (fd);
}

/*

	Dans cette fonctino on va simplement remplacer, dans la ligne recuperee, les $variable
	par leur valeur dans l'environnement. Sauf si ils sont dans des simple quotes

*/

int    mini_expand(t_lst *tmp, t_mini *data)
{
	int     i;
	int     c;
	int     j;

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