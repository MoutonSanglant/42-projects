/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/15 04:17:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 12 lignes
static int		get_next_datas(const int fd, char *left_over, char *buf)
{
	// la valeur de retour (nombre d'octets écrits dans *line)
	int		rcount;

	// pas de reliquat, lecture dans le fichier
	if (*left_over == '\0')
		rcount = read(fd, buf, BUFF_SIZE);
	// sinon...
	else
	{
		// longueur du reliquat
		rcount = ft_strlen(left_over);
		// copie du reliquat dans le buffer
		ft_memcpy(buf, left_over, rcount);
		// nettoyage du reliquat
		ft_bzero(left_over, BUFF_SIZE);
	}
	// césure de la chaine
	buf[rcount] = '\0';
	return (rcount);
}

// 24 lignes
static int		read_line(const int fd, char **line, char *left_over,
															size_t offset)
{
	// le left_over de lecture
	char	buf[BUFF_SIZE + 1];
	// un pointeur sur le charactère de fin de ligne
	char	*eol;
	// la taille de la chaine
	int		length;
	// la valeur de retour (nombre d'octets écrits dans *line)
	int		rcount;

	// lecture des données (fichier ou relicat)
	if ((rcount = get_next_datas(fd, left_over, buf)) < 0)
		return (-1);
	// si rien n'a été lu à la première itération de la récursive: EOF
	if (rcount == 0 && offset < 1)
		return (0);
	// si rien n'a été lu OU '\n' présent
	if (rcount == 0 || (eol = ft_strchr(buf, '\n')))
	{
		// si au moins 1 caractère a été lu (cas du '\n')
		if (rcount)
		{
			// la taille de la chaine correspond au nombre d'octets écrits
			length = rcount;
			// on ne comptabilise que les caractères avant le '\n'
			rcount = eol - buf;
			// écriture du reliquat
			ft_memmove(left_over, &buf[rcount + 1], length - rcount);
		}
		// on incrémente la taille de la chaine
		length = offset + rcount;
		// allocation de l'espace nécessaire pour la ligne entière'
		*line = (char *)malloc(length + 1);
		(*line)[length] = '\0';
	}
	// sinon, récursion en décalant l'offset du nombre de caractères lus'
	else if ((length = read_line(fd, line, left_over, offset + rcount)) <= 0)
		return (length);
	// copie du buffer dans la nouvelle chaine
	ft_memcpy(&(*line)[offset], buf, rcount);
	return ((rcount) ? rcount : 1);
}

// 23 lignes
static int		index_lines(const int fd, char **line, t_gnl *p_fd, int idx)
{
	// un pointeur sur une ligne dans la liste
	t_line	*p_line;
	// un pointeur sur la précédente ligne
	t_line	*p_prev;
	// la valeur de retour (nombre d'octets écrits dans *line)
	int		rcount;

	rcount = 1;
	// pointeur sur la première ligne
	p_line = p_fd->lines;
	// boucle pour pointer sur le dernier élément de la listeé
	while (p_line && p_line->next)
		p_line = p_line->next;
	// boucle tant que l'index est supérieur au nombre de ligne enregistré
	while (idx > p_fd->count)
	{
		// lecture de la ligne
		if ((rcount = read_line(fd, line, p_fd->buf, 0)) <= 0)
			return (rcount);
		// pointeur sur la ligne actuelle
		p_prev = p_line;
		// on alloue un nouveau maillon
		if (!(p_line = (t_line *)ft_memalloc(sizeof(t_line))))
			return (-1);
		// la liste est vide, on insert en première position
		else if (!p_fd->lines)
			p_fd->lines = p_line;
		// on insert à la suite
		else
			p_prev->next = p_line;
		// on enregiste la chaine dans le maillon
		p_line->content = *line;
		// on incrémente le compteur de lignes
		p_fd->count++;
	}
	return ((rcount) ? rcount : 1);
}

// 24 lignes
static int		get_indexed_line(const int fd, char **line, t_gnl *p_fd,
																	int idx)
{
	// un pointeur sur une ligne de la liste
	t_line	*p_line;
	// la valeur de retour (nombre d'octets écrits dans *line)
	int		rcount;

	// mise à null de *line (cas ou un index vient d'être spécifié')
	*line = NULL;
	// un index < 0 correspond à un nettoyage de la liste
	if (idx < 0)
	{
		// boucle qui nettoie tous les maillons
		while ((p_line = p_fd->lines))
		{
			// on utilise un second pointeur pour parcourir les maillons
			p_fd->lines = p_line->next;
			// libération du maillon courant (chaine puis maillon)
			ft_strdel(&p_line->content);
			ft_memdel((void **)p_line);
		}
		// on retourne -1 pour nettoyer la structure et libérer le fd
		return (-1);
	}
	// un index == 0 correspond à la récupération de la prochaine ligne
	else if (idx == 0)
		idx = (p_fd->idx) ? p_fd->idx : 1;
	// on enregistre les lignes dans la liste
	if ((rcount = index_lines(fd, line, p_fd, idx)) <= 0)
		return (rcount);
	// on incrémente l'index de lecture (permet de conserver l'état de lecture)
	p_fd->idx = idx + 1;
	// pointeur sur la première ligne
	p_line = p_fd->lines;
	// boucle pour pointer sur l'élément à l'index spécifié
	while (--idx)
		p_line = p_line->next;
	// on copie la chaine dans le pointeur
	*line = ft_strdup(p_line->content);
	return ((rcount = ft_strlen(*line)) ? rcount : 1);
}

/*
** Amélioration: allouer les structures sur le tas (heap) pour
** éviter de limiter la pile (stack) du programme
*/
// 22 lignes
int				get_next_line(const int fd, char **line)
{
	// BONUS: un tableau de structures pour chaque fd (fd < 0 <=> fd libre)
	static t_gnl	fd_table[MAX_FD] = { [0 ... MAX_FD - 1] = { .fd = -1 } };
	// un pointeur sur une structure du tableau
	t_gnl			*p_fd;
	// la valeur de retour (nombre d'octets écrits dans *line)
	int				rcount;

	// le buffer n'est pas bon, ou line ne pointe pas vers une adresse
	if (fd < 0 || !line)
		return (-1);
	// pointeur sur le début du tableau
	p_fd = fd_table;
	// on cherche la structure qui correspond (si il y a) au fd dans le tableau
	while (BUSY_FD(p_fd, fd) && p_fd < fd_table + MAX_FD - 1)
		p_fd++;
	// si le dernier élément est occupé, le tableau est plein
	if (BUSY_FD(p_fd, fd))
		return (-1);
	// structure récupérée, on enregistre le fd dedans
	p_fd->fd = fd;
	// BONUS: parsing de l'index dans *line
	// BONUS: on récupère la ligne correspondante
	if (*line || p_fd->idx)
		rcount = get_indexed_line(fd, line, p_fd, ft_atoi(*line));
	// sinon, on lit la prochaine ligne
	else
		rcount = read_line(fd, line, p_fd->buf, 0);
	// si fin du fichier atteinte, on nettoie la structure
	if (rcount <= 0)
	{
		ft_bzero(p_fd, sizeof(t_gnl));
		// libère le fd
		p_fd->fd = -1;
	}
	return (rcount);
}
