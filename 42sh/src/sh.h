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

# include <curses.h>
# include <term.h>
# include <termios.h>

# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <includes/libft.h>

# define PROGRAM_NAME "minishell"

typedef struct	s_sh_datas
{
	char	**environ;
	char	*prompt;
}				t_sh_datas;

typedef struct	s_env_datas
{
	char	**environ;
	char	**utility;
}				t_env_datas;

typedef enum	e_env_error
{
	ENVERR_VERB,
	ENVERR_PATH,
	ENVERR_SPLIT,
	ENVERR_UNSET
}				t_env_error;

/*
********************************************************************************
**								:: Built-ins ::								   *
********************************************************************************
*/

/*
**								: builtins.c :
*/
int				check_builtins(char **argv, t_sh_datas *sh_datas);

/*
**								: exit.c :
*/
void			sh_exit(char **argv, t_sh_datas *sh_datas);

/*
**								: environ.c :
*/
char			**get_environ(char **environ, const char *name);
char			**set_environ(char **environ, const char *name,
								const char *value, int override);
char			**unset_environ(char **environ, const char *name);

/*
**									: env.c :
*/
void			env(char **argv, t_sh_datas *sh_datas);
int				env_error(t_env_error err);

/*
**								: cpy_environ.c :
*/
char			**cpy_environ(char **environ);

/*
**								: create_default_environ.c :
*/
char			**create_default_environ(char **environ);

/*
**									: cd.c :
*/
int				cd(char *path, t_sh_datas *sh_datas);

/*
********************************************************************************
**								:: Parser ::								   *
********************************************************************************
*/

/*
**								: parser.c :
*/
char			**parse_input(char *command);

/*
********************************************************************************
**								:: Processes ::								   *
********************************************************************************
*/

/*
**								: process.c :
*/
int				run_exec(char **argv, t_sh_datas *sh_datas, char **exec_env);

/*
********************************************************************************
**								:: Prompt ::								   *
********************************************************************************
*/

/*
**								: prompt.c :
*/
void			set_prompt(t_sh_datas *sh_datas);

/*
********************************************************************************
**								:: Termcaps ::								   *
********************************************************************************
*/

/*
**								: termcaps.c :
*/
int		termcaps_init(struct termios *term);

/*
********************************************************************************
**								:: Helpers ::								   *
********************************************************************************
*/

/*
**								: unescape.c :
*/
char			**unescape(char **input_blocks);

#endif
