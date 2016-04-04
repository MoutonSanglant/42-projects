/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:13:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/15 02:13:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <includes/libft.h>

/*
** Consignes
** =========
** Affiche un prompt (par exemple '$> ')
** Attente d'entree utilisateur
** Prompt affiche a nouveau apres execution de la commande
** Les executables sont ceux que l'on trouve dans PATH
** Si l'executable n'est pas trouve, afficher un message d'erreur (ne pas utiliser errno)
** Utiliser char **environ system pour gerer le PATH et l'environnement
** builtins a gerer: cd, setenv, unsetenv, env, exit
** Fonctions
** =========
**	opendir
**	readdir
**	closedir
**	malloc
**	free
**	exit
**	*getcwd
**	*chdir
**	*fork
**	stat
**	lstat
**	*fstat
**	open
**	close
**	read
**	write
**	*execve
**	*access
**	*wait
**	*waitpid
**	*wait3
**	*wait4
**	*signal
**	*kill
*/

typedef struct	s_sh_datas
{
	char	*prompt;
}				t_sh_datas;

/*
********************************************************************************
**									:: Built-ins ::							   *
********************************************************************************
*/

/*
**									: builtins.c :
*/
int		check_builtins(char **argv);

/*
**									: environ.c :
*/
void	init_environ();
void	print_environ();

/*
**										: cd.c :
*/
int		cd(char *path, t_sh_datas *sh_datas);

/*
********************************************************************************
**									:: Prompt ::							   *
********************************************************************************
*/

/*
**									: prompt.c :
*/
void	set_prompt(t_sh_datas *sh_datas);


#endif
