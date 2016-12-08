/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/08 20:58:51 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

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
	ft_putstr("[DEBUG] KEEP buf: ");
	ft_putendl(buf);
	ft_putstr("[DEBUG] keep: ");
	ft_putendl(gnl_st->keep);
		lst_el = ft_lstnew(NULL, len + ft_strlen(gnl_st->keep));
		lst_el->content = (char *)malloc(len + ft_strlen(gnl_st->keep) + 1);
		lst_el->content = ft_memcpy(lst_el->content, gnl_st->keep, ft_strlen(gnl_st->keep));
		ft_memcpy(&lst_el->content[ft_strlen(gnl_st->keep)], buf, len);
		((char *)lst_el->content)[len + ft_strlen(gnl_st->keep)] = '\0';
	ft_putstr("[DEBUG] content: ");
	ft_putendl((char *)lst_el->content);
		if (gnl_st->lines)
			gnl_st->last->next = lst_el;
		else
			gnl_st->lines = lst_el;
		gnl_st->keep = NULL;
		if (!eol)
			return ;
		buf = eol + 1;
		gnl_st->count++;
	}
	while ((eol = find_eol(buf)))
	{
		*eol = '\0';
		lst_el = ft_lstnew(ft_strdup(buf), eol - buf);
		ft_putstr("[DEBUG] buf: ");
		ft_putendl(buf);
		if (gnl_st->lines)
			gnl_st->last->next = lst_el;
		else
			gnl_st->lines = lst_el;
		gnl_st->last = lst_el;
		ft_putstr("[DEBUG] new: ");
		ft_putendl((char *)lst_el->content);
		ft_putstr("[DEBUG] last: ");
		ft_putendl((char *)gnl_st->last->content);
		ft_putendl("=============");
		buf = eol + 1;
		gnl_st->count++;
	}
	// TODO
	// conserver keep sous forme de liste afin de pouvoir concatener
	// toutes les occurences en l'absence de \n
	gnl_st->keep = ft_strdup(buf);
	//ft_putendl(gnl_st->keep);
	ft_putstr("[DEBUG] count: ");
	ft_putnbr(gnl_st->count);
	ft_putchar('\n');
	//gnl_st->count--;
}


int		get_next_line(const int fd, char **line)
{
	static t_gnl	gnl_st = { .lines = NULL, .count = 0, .idx = 0, .keep = NULL };
	char	buf[BUFF_SIZE + 1];
	int		ret;

	ft_putendl("[DEBUG] GNL CALL: ");
	if (fd < 0)
		return (-1);
	if (*line)
	{
		//lineno = ft_atoi(*line);
		gnl_st.idx = (int)*line - 1;
		// user force a flush of gnl buffer
		if (gnl_st.idx < 0)
			return (-1);
	}
	ft_putstr("[DEBUG] idx: ");
	ft_putnbr(gnl_st.idx);
	ft_putchar('\n');
	// tant qu'on a pas la ligne demande...
	while (gnl_st.idx >= gnl_st.count)
	{
		// on lit les lignes dans le buffer
		if ((ret = read(fd, buf, BUFF_SIZE)) >= 0)
		{
			buf[ret] = '\0';
			if (ret == 0)
				return (0);
			// on split le buffer pour chaque \n
			//store_lines(&gnl_st, ft_strsplit(buf, '\n'));
			store_lines(&gnl_st, buf);
			// la derniere ligne est soit une ligne tronquee, soit c'est
			// la derniere ligne du fichier (EOF)

			// Si c'est le cas, il faut gere ca dans store_lines
		}
		else
		{
			// Apparement, l'utilisateur demande une ligne inexistante, on renvoie -1
			return (-1);
		}
	}
	/*
	ft_putstr("[DEBUG] lineno: ");
	ft_putnbr(lineno);
	ft_putchar('\n');
	*/
	//*line = ft_strdup((const char *)ft_lstgetat(gnl_st.lines, lineno)->content);
	*line = ft_strdup((char *)lstgetat(gnl_st.lines, gnl_st.idx)->content);
	gnl_st.idx += 1;
	return (1);
}
