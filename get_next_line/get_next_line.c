/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/09 20:29:08 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//t_list	*lstgetat(t_list *lst, int idx)
t_2tree	*lstgetat(t_2tree *lst, int idx, int dir)
{
	if (idx < 0)
	{
		while (BRANCH(lst, dir))
			lst = BRANCH(lst, dir);
		return (lst);
	}
	while (idx > 0)
	{
		lst = BRANCH(lst, dir);
		if (!lst)
			break ;
		idx--;
	}
	return (lst);
}

void	store_lines(t_gnl *gnl_st, t_2tree *last, char *buf)
{
//t_2tree	*lst_el;
	//t_list	*lst_el;
	char	*eol;
	//int		len;

	/*
	// si un troncon de chaine est present dans 'keep'
	//if (gnl_st->keep)
	if (last->right)
	{
		eol = ft_strchr(buf, '\n');
		if (eol)
		{
			*eol = '\0';
			len = eol - buf;
		}
		else
			len = ft_strlen(buf);
		//lstgetat(gnl_st->keep, -1)->next = ft_lstnew(ft_strdup(buf), len + 1);
		//((char *)lstgetat(gnl_st->keep, -1)->content)[len] = '\0';
		//last->right = ft_lstnew(ft_strdup(buf), len + 1); // !!!
		last->right = (t_2tree *)malloc(sizeof(t_2tree));
		last->right->left = NULL;
		last->right->right = NULL;
		last->right->content = ft_strdup(buf);
		//((char *)lstgetat(last->right, -1)->content)[len] = '\0';
		//((char *)last->right->content)[len] = '\0';
		last->right->content[len] = '\0';
		if (!eol)
			return ;
		int	total_size = 0;
		//lst_el = gnl_st->keep;
		lst_el = last->right;
		while (lst_el)
		{
			total_size += ft_strlen(lst_el->content);
			//lst_el = lst_el->next;
			lst_el = lst_el->left;
		}
		//last->next = ft_lstnew(NULL, total_size + 1);
		//last->next->content = malloc(total_size + 1);
		//last->left = ft_lstnew(NULL, total_size + 1);
		last->left = (t_2tree *)malloc(sizeof(t_2tree));
		last->left->left = NULL;
		last->left->right = NULL;
		last->left->content = malloc(total_size + 1);
		//lst_el = gnl_st->keep;
		lst_el = last->right;
		int idx = 0;
		while (lst_el)
		{
			len = ft_strlen(lst_el->content);
			//ft_memcpy(&last->next->content[idx], lst_el->content, len);
			ft_memcpy(&last->left->content[idx], lst_el->content, len);
			//lst_el = lst_el->next;
			lst_el = lst_el->left;
			idx += len;
		}
		//((char *)last->next->content)[idx] = '\0';
		((char *)last->left->content)[idx] = '\0';
		//gnl_st->keep = NULL; // LEAK, I need to handle frees
		//last = last->next;
		//gnl_st->keep = NULL; // LEAK, I need to handle frees
		last = last->left;
		buf = eol + 1;
		gnl_st->count++;
	}*/

	// tant qu'on trouve un '\n' dans le buffer
	//while ((eol = ft_strchr(buf, '\n')))
	while (1) // recurse ? :)
	{
		t_2tree *lastright;

		eol = ft_strchr(buf, '\n');
		if (eol)
			*eol = '\0';
		ft_putstr("[DEBUG] BUFFER: ");
		ft_putendl(buf);
		/*
		//lst_el = ft_lstnew(ft_strdup(buf), eol - buf + 1);
		lst_el = (t_2tree *)malloc(sizeof(t_2tree));
		lst_el->left = NULL;
		lst_el->right = NULL;
		lst_el->content = ft_strdup(buf);
		*/
		//((char *)lst_el->content)[eol - buf] = '\0';
		//last->next = lst_el;
		//last = lst_el;
		lastright = lstgetat(last, -1, TREE_RIGHT);
		if (!lastright->content)
		{
			ft_putendl("[DEBUG] STORE CONTENT");
			lastright->content = ft_strdup(buf);
			lastright->left = NULL;
			lastright->right = (t_2tree *)malloc(sizeof(t_2tree));
			lastright = lastright->right;
			lastright->left = NULL;
			lastright->right = NULL;
			buf = eol + 1;
		}
		//lastright->right = lst_el;
		//lastright = lastright->right;
		//lastright->content = ft_strdup(buf);
		/*
		if (eol)
		{
			ft_putendl("[DEBUG] left");
			last->left = (t_2tree *)malloc(sizeof(t_2tree));
			//last->left = NULL;
			last->right = NULL;
			last->content = NULL;
			//last = lst_el;
			buf = eol + 1;
			gnl_st->count++;
		}*/
		if (!eol)
		{
			ft_putendl("[DEBUG] right");

			//last->left = lst_el;
			//last = lst_el;

			//len = ft_strlen(buf);
			//lastright->right = lst_el;
			//lastright->right = NULL;
			//lastright->left = NULL;
			/*
			lastright->right = (t_2tree *)malloc(sizeof(t_2tree));
			ft_putendl("[DEBUG] CCC");
			lastright->right->left = NULL;
			lastright->right->right = NULL;
	ft_putstr("[DEBUG] to right: ");
	ft_putendl(buf);
			lastright->right->content = ft_strdup(buf);
			lastright->right->content[len] = '\0';
			//*/
			break ;
		}
		else
		{
			ft_putendl("[DEBUG] left");
			last->left = (t_2tree *)malloc(sizeof(t_2tree));
			last = last->left;
			last->content = ft_strdup(buf);
			last->left = NULL;
			last->right = NULL;
			gnl_st->count++;
		}
	}

	// Une logique
	// SI !left remplir LEFT
	// SINON remplir LAST RIGHT
	// devrait suffire !!


	/*
	// on conserve le reste, si il y en a un
	len = ft_strlen(buf);
	if (len > 0)
	{
		//gnl_st->keep = ft_lstnew(ft_strdup(buf), len + 1);
		//last->right = ft_lstnew(ft_strdup(buf), len + 1);
		//((char *)gnl_st->keep->content)[len] = '\0';
		//((char *)last->right->content)[len] = '\0';
		last->right = (t_2tree *)malloc(sizeof(t_2tree));
		last->right->left = NULL;
		last->right->right = NULL;
		last->right->content = ft_strdup(buf);
		last->right->content[len] = '\0';
	}
	*/
}

static void	store_whole_line(char **line, t_2tree *node)
{
	t_2tree	*root;
	int		size;
	int		wcount;
	int		len;

	if (!node->right)
	{
		*line = ft_strdup(node->content);
		return ;
	}

	root = node;
	size = 0;
	ft_putendl("[DEBUG] store ");
	while(node)
	{
	ft_putendl("[DEBUG] node ");
		size += ft_strlen(node->content);
		node = node->right;
	}
	*line = (char *)malloc(size + 1);
	(*line)[size] = '\0';

	wcount = 0;
	node = root;
	while (node)
	{
		len = ft_strlen(node->content);
	ft_putstr("[DEBUG] write: ");
	ft_putstr(node->content);
	ft_putstr(" = ");
	ft_putnbr(len);
	ft_putchar('\n');
		ft_memcpy(&(*line)[wcount], node->content, len);
		node = node->right;
		wcount += len;
	}
}

/*
**	ft_putstr("[DEBUG] idx: ");
**	ft_putnbr(gnl_st.idx);
**	ft_putchar('\n');
*/

int		get_next_line(const int fd, char **line)
{
	static t_gnl	gnl_st = { .lines = NULL, .count = 0, .idx = 0 };
	char			buf[BUFF_SIZE + 1];
	int				ret;

	ft_putendl("[DEBUG] gnl call");
	// si le fd est négatif... ou qu'un index est spécifié et qu'il est négatif'
	if (fd < 0 || (*line && (gnl_st.idx = (int)*line - 1) < 0))
		return (-1);
	// si aucune ligne n'a été lue, on créé un noeud vide et `last` pointe dessus
	if (!gnl_st.lines)
	{
		gnl_st.lines = (t_2tree *)malloc(sizeof(t_2tree));
		gnl_st.lines->left = NULL;
		gnl_st.lines->right = NULL;
		gnl_st.lines->content = NULL;
	}
	// tant que la ligne demandee n'a pas été stockée
	while (gnl_st.idx >= gnl_st.count)
	{
		// on stocke les charactères du fichier dans le buffer
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			// on récupère la/les lignes stockés dans le buffer
			store_lines(&gnl_st, lstgetat(gnl_st.lines, -1, TREE_LEFT), buf);
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
	store_whole_line(line, lstgetat(gnl_st.lines, gnl_st.idx, TREE_LEFT));
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
