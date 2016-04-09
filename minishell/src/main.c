/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/09 16:32:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

static void		del_it(void *content, size_t size)
{
	(void) content;
	(void) size;
	return ;
}

static t_list	*del_elem(t_list *elem)
{
	t_list	*next;

	next = elem->next;
	ft_lstdelone(&elem, &del_it);
	return (next);
}

static char		**remove_escape_characters(char **str)
{
	char	*new_str;
	int		count;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i])
	{
		j = 0;
		count = 0;
		while (str[i][j])
			if (str[i][j++] == '\\')
				count++;
		new_str = ft_strnew(ft_strlen(str[i]) - count);
		j = 0;
		k = 0;
		while (str[i][j])
		{
			if (str[i][j] != '\\')
			{
				new_str[k] = str[i][j];
				k++;
			}
			j++;
		}
		ft_strdel(&str[i]);
		str[i] = new_str;
		i++;
	}
	return (str);
}

static char		**parse_input(char *command)
{
	char	**out;
	t_list	*word_list;
	t_list	*start;
	char	*word;
	char	*tmp;
	int		i;

	start = NULL;
	while (*command && *command == ' ')
		command++;
	if (*command == '\0')
	{
		out = (char **)ft_memalloc(sizeof(char *));
		out [0] = NULL;
		return (out);
	}
	i = 0;
	word = NULL;
	while (1)
	{
		if (!word)
			word = &command[i];
		if (command[i] == '\\')
			i++;
		else if (ft_isspace(command[i]) || command[i] == '\0')
		{
			tmp = ft_strnew(i);
			ft_strncpy(tmp, word, i);
			word = NULL;
			if (!start)
			{
				word_list = ft_lstnew((void *)tmp, i);
				start = word_list;
			}
			else
			{
				word_list->next = ft_lstnew((void *)tmp, i);
				word_list = word_list->next;
			}
			command = &command[i + 1];
			i = 0;
			if (command[i] == '\0')
				break ;
			continue ;
		}
		i++;
	}
	word_list = start;
	out = (char **)ft_memalloc(sizeof(char *) * ft_lstsize(start) + 1);
	i = 0;
	while (word_list)
	{
		out[i] = (char *)word_list->content;
		word_list = del_elem(word_list);
		i++;
	}
	out [i] = NULL;
	out = remove_escape_characters(out);
	return (out);
}

static int		read_input(char **argv, t_sh_datas *sh_datas)
{
	int		ret_val;

	if ((ret_val = check_builtins(argv, sh_datas)) >= 0)
		return (ret_val);
	else
		return (run_exec(argv, sh_datas, NULL));
	return (0);
}

int				main(void)
{
	extern char		**environ;
	char			**argv;
	char			*line;
	t_sh_datas		sh_datas;
	int				i;

	sh_datas.environ = create_default_environ(environ);
	set_prompt(&sh_datas);
	while (1)
	{
		ft_putstr(sh_datas.prompt);
		if (get_next_line(1, &line))
		{
			argv = parse_input(line);
			read_input(argv, &sh_datas);
			i = 0;
			while (argv[i])
				ft_strdel(&argv[i++]);
			ft_memdel((void **)&argv);
			ft_strdel(&line);
		}
	}
	return (0);
}
