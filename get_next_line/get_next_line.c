/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/10 17:42:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 16 lignes
static int		flush_btree(t_btree **btree)
{
	t_btree	*left;
	t_btree	*right;

	if (!*btree)
		return (-1);
	left = (*btree)->left;
	right = (*btree)->right;
	if (left)
		flush_btree(&left);
	if (right)
		flush_btree(&right);
	free((*btree)->content);
	free(*btree);
	*btree = NULL;
	return (-1);
}

// 10 lignes
static t_btree	*b_search(t_btree *btree, size_t idx, int side)
{
	size_t	n;

	n = 0;
	while (BRANCH(btree, side))
	{
		if (n++ == idx)
			break ;
		btree = BRANCH(btree, side);
	}
	return (btree);
}

// 22 lignes
static int		cpy_line(char **line, t_btree *node)
{
	int		length;
	int		offset;

	// si le noeud existe mais ne contient pas de données (dernière ligne)
	if (!node->content)
		return (0);
	// si il n'y a pas de noeud à droite (la ligne est entière)
	if (!node->right)
	{
		*line = ft_strdup(node->content);
		return (node->length + 1);
	}
	length = node->length;
	// allocation de l'espace nécessaire à la chaîne
	*line = (char *)malloc(length + 1);
	// charactère de fin de chaîne
	(*line)[length] = '\0';
	// marqueur de décalage dans la mémoire
	offset = 0;
	// tant que la chaîne n'est pas terminée...
	while (node)
	{
		// taille de la chaîne
		length = ft_strlen(node->content);
		// copie de la chaîne vers 'line' décalé de 'offset' octet
		ft_memcpy(&(*line)[offset], node->content, length);
		// récupération du maillon suivant
		node = node->right;
		// incrémentation de l'offset
		offset += length;
	}
	return (offset + 1);
}

// 25 lignes
static int		push(t_btree *last, char *buf)
{
	t_btree *right;
	char	*eol;
	int		n_count;

	// par défaut, on estime que les lignes sont terminées par '\n'
	n_count = 1;
	// si le tampon est vide, on aborte
	if (*buf == '\0')
		return (0);
	// on récupère l'élément le plus à droite
	right = b_search(last, -1, TREE_RIGHT);
	// si celui-ci contient déjà des données (cas d'une ligne tronquée')
	if (right->content)
	{
		// dans ce cas, le compteur a déjà été incrémenté, pas d'incrémentation
		n_count = 0;
		// création du prochain noeud 'droite'
		right->right = (t_btree *)ft_memalloc(sizeof(t_btree));
		// positionnement sur le noeud créé
		right = right->right;
	}
	// dans le cas ou un '\n' est présent dans le buffer
	if ((eol = ft_strchr(buf, '\n')))
	{
		// on remplace le '\n' par un '\0' pour faciliter strdup
		*eol = '\0';
		// on copie la portion de buffer dans le noeud le plus à droite
		right->content = ft_strdup(buf);
		last->length += ft_strlen(buf);
		// on créé un noeud à gauche
		last->left = (t_btree *)ft_memalloc(sizeof(t_btree));
		// appel récursif sur l'élément 'left' pour récupérer le reste du tampon
		return (push(last->left, eol + 1) + n_count);
	}
	// pas de '\n' présent
	// on copie le reste du buffer dans le noeud le plus à droite
	right->content = ft_strdup(buf);
	last->length += ft_strlen(buf);
	return (n_count);
}

/*
**	ft_putstr("[DEBUG] idx: ");
**	ft_putnbr(gnl_st.idx);
**	ft_putchar('\n');
*/

// 25 lignes
int				get_next_line(const int fd, char **line)
{
	static t_gnl	gnl_st = { .lines = NULL, .count = 0, .idx = 0, .eof = 0 };
	char			buf[BUFF_SIZE + 1];
	int				ret;

	// si le fd est négatif... ou qu'un index est spécifié et qu'il est négatif'
	if (fd < 0 || (*line && (gnl_st.idx = ft_atoi(*line)) < 0))
		return (flush_btree(&gnl_st.lines));
	// si la fin du fichier est atteint
	if (gnl_st.eof)
		return (0);
	// si aucune ligne n'a été lue, on créé un noeud vide
	if (!gnl_st.lines)
		gnl_st.lines = (t_btree *)ft_memalloc(sizeof(t_btree));
	// tant que la ligne demandée n'a pas été stockée
	while ((ret = read(fd, buf, BUFF_SIZE)) >= 0)
	{
		// on stocke les charactères du fichier dans le buffer
		buf[ret] = '\0';
		// on récupère la/les lignes stockés dans le buffer
		gnl_st.count += push(b_search(gnl_st.lines, -1, TREE_LEFT), buf);
		// si on a récupéré suffisament de lignes
		if (gnl_st.count > gnl_st.idx + 1)
			break ;
		// si on est arrivé au bout du fichier
		if (ret == 0)
		{
			gnl_st.eof = 1;
			break ;
		}
	}
	// si l'utilisateur demande une ligne inexistante, on renvoie -1
	if (gnl_st.idx > gnl_st.count || ret < 0)
		return (-1);
	// on stocke dans `line` une copie de la ligne à l'index `idx`
	// PUIS on incrémente idx
	// PUIS on renvoie le nombre de caractères lus
	return (cpy_line(line, b_search(gnl_st.lines, gnl_st.idx++, TREE_LEFT)));
}
