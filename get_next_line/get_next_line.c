/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/09 01:19:03 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_eol(char *s)
{
	while (*s != '\n')
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (s);
}

t_list	*lstgetat(t_list *lst, int idx)
{
	if (idx < 0)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	while (idx > 0)
	{
		lst = lst->next;
		if (!lst)
			break ;
		idx--;
	}
	return (lst);
}

void	store_lines(t_gnl *gnl_st, char *buf)
{
	t_list	*lst_el;
	char	*eol;
	int		len;

	if (gnl_st->keep)
	{
		eol = find_eol(buf);
		if (eol)
		{
			*eol = '\0';
			len = eol - buf;
		}
		else
			len = ft_strlen(buf);
		lstgetat(gnl_st->keep, -1)->next = ft_lstnew(ft_strdup(buf), len + 1);
		((char *)lstgetat(gnl_st->keep, -1)->content)[len] = '\0';
		if (!eol)
			return ;
		int	total_size = 0;
		lst_el = gnl_st->keep;
		while (lst_el)
		{
			total_size += ft_strlen(lst_el->content);
			lst_el = lst_el->next;
		}
		gnl_st->last->next = ft_lstnew(NULL, total_size + 1);
		gnl_st->last->next->content = malloc(total_size + 1);
		lst_el = gnl_st->keep;
		int idx = 0;
		while (lst_el)
		{
			len = ft_strlen(lst_el->content);
			ft_memcpy(&gnl_st->last->next->content[idx], lst_el->content, len);
			lst_el = lst_el->next;
			idx += len;
		}
		((char *)gnl_st->last->next->content)[idx] = '\0';
		gnl_st->keep = NULL; // LEAK, I need to handle frees
		gnl_st->last = gnl_st->last->next;
		buf = eol + 1;
		gnl_st->count++;
	}
	while ((eol = find_eol(buf)))
	{
		*eol = '\0';
		lst_el = ft_lstnew(ft_strdup(buf), eol - buf + 1);
		((char *)lst_el->content)[eol - buf] = '\0';
		gnl_st->last->next = lst_el;
		gnl_st->last = lst_el;
		buf = eol + 1;
		gnl_st->count++;
	}
	gnl_st->keep = ft_lstnew(ft_strdup(buf), ft_strlen(buf) + 1);
	((char *)gnl_st->keep->content)[ft_strlen(buf)] = '\0';
}

/*
**	ft_putstr("[DEBUG] idx: ");
**	ft_putnbr(gnl_st.idx);
**	ft_putchar('\n');
*/

int		get_next_line(const int fd, char **line)
{
	static t_gnl	gnl_st = { .lines = NULL, .count = 0, .idx = 0, .keep = NULL };
	char			buf[BUFF_SIZE + 1];
	int				ret;

	// si le fd est négatif... ou qu'un index est spécifié et qu'il est négatif'
	if (fd < 0 || (*line && (gnl_st.idx = (int)*line - 1) < 0))
		return (-1);
	// si aucune ligne n'a été lue, on créé un noeud vide et `last` pointe dessus
	if (!gnl_st.lines)
	{
		gnl_st.lines = ft_lstnew(NULL, 0);
		gnl_st.last = gnl_st.lines;
	}
	// tant que la ligne demandee n'a pas été stockée
	while (gnl_st.idx >= gnl_st.count)
	{
		// on stocke les charactères du fichier dans le buffer
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			// on récupère la/les lignes stockés dans le buffer
			store_lines(&gnl_st, buf);
		}
		// si l'utilisateur demande une ligne inexistante, on renvoie -1
		if (gnl_st.idx > gnl_st.count || ret < 0)
			return (-1);
		// sinon, on est arrivé au bout du fichier
		else if (ret == 0)
			return (0);
	}
	// on incremente l'index (0 correspond a un noeud vide)
	gnl_st.idx += 1;
	// on stocke dans `line` une copie de la ligne à l'index `idx`
	*line = ft_strdup((char *)lstgetat(gnl_st.lines, gnl_st.idx)->content);
	return (1);
}
/*
**	if (fd < 0)
**		return (-1);
**	if (*line)
**	{
**		// on récupère l'index envoyé par l'utilisateur
**		gnl_st.idx = (int)*line - 1;
**		// si l'index est inférieur a 1, l'utilisateur force le flush du buffer'
**		if (gnl_st.idx < 0)
**			return (-1);
**	}
*/
