/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 04:19:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/19 06:36:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Definitions:
** ------------
** # -> commentaire
** ## -> commande
** [:print:] [:digit:] [:digit] -> salle x y
** [:print:]-[:print:] -> liaison salle-salle
** L -> reservé
** 'erreur ou vide' -> fin acquisition (exécution programme)
**
** Commandes:
** ----------
** ##start -> debut fourmiliere
** ##end -> fin fourmiliere
** ##??? -> ignoré
**
** Programme:
** ----------
** Données insufisante: afficher 'ERROR'
**
** Contraintes:
** ------------
** Nombre fourmi / salle: 1 max
** Nombre fourmi 'start' / 'end': infini
** Les fourmis commencent toutes sur 'start'
**
** Output:
** -------
** X
** ##start
** 0 1 0
** ##end
** 1 5 0
** 2 9 0
** 0-2
** 0-1
**
** L1-2
** L1-3 L2-2
** L1-4 L2-3 L3-2
** L2-4 L3-3
** L3-4
**
** ---------
** partie 1:
** fourmiliere
** > nb fourmi
** > salles
** > connections
** partie 2:
** déplacements
** (L#fourmi-destination)
**
** Fonctions:
** ----------
** read
** write
** malloc
** free
** perror
** strerror
** exit
*/



/*
static void	output(t_queue *queue, char *str)
{
	ft_printf("queue size: %o\n", ft_queuesize(queue));
	while (queue)
	{
		ft_printf("%s: %s\n", str, (char *)queue->content);
		ft_queuepop(&queue);
		//lst = lst->next;
	}
}
*/

static int	get_command(char *str)
{
	if (ft_strequ(str, "#start"))
		return (1);
	if (ft_strequ(str, "#end"))
		return (2);
	return (0);
}

static int	parse_input(char *line, void *st)
{
	t_input		*input;
	static int	command = 0;

	input = (t_input *)st;

	if (line[0] == 'L')
		return (0);
	if (line[0] == '#')
	{
		command = get_command(&line[1]);
		return (1);
	}

	if (input->state == 0)
	{
		input->ant_count = ft_atoi(line);
		if (input->ant_count < 1)
			error("ant_count < 1");
		input->state++;
	}
	else if (input->state == 1)
	{
		if (!new_room(&input->rooms, line))
			input->state++;
		(void)command;
	}

	if (input->state == 2)
	{
		if (!new_connection(&input->connections, line))
			input->state++;
	}

	command = 0;
	return ((input->state) != 3);

	//f->str = ft_strjoin(f->str, line);
}

int main(int argc, char **argv)
{
	t_input	input;

	if (argc < 1 && !*argv[0])
		return (1);
	ft_printf("lem_in\n");
	//input.graph = NULL;
	input.rooms = NULL;
	input.connections = NULL;
	input.state = 0;
	input.ant_count = -1;
	read_stdin(&parse_input, (void*)&input);
	input.graph = new_graph(input.rooms, input.connections);
	//ft_printf("%s\n", f.str);
	ft_printf("exit\n");
	return (0);
}
