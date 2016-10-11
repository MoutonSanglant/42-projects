/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 04:19:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/11 13:14:53 by tdefresn         ###   ########.fr       */
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




static void	dequeue(t_queue *queue)
{
	//ft_printf("queue size: %o\n", ft_queuesize(queue));
	while (queue)
	{
		//ft_printf("%s: %s\n", str, (char *)queue->content);
		//ft_printf("%s\n", (char *)queue->content);
		ft_queuepop(&queue);
	}
}


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
	else if (input->state == 1 && !new_room(input, line, command))
		input->state++;
	if (input->state == 2 && !new_connection(&input->connections, line))
		input->state++;
	command = 0;
	return ((input->state) != 3);
}

int main(int argc, char **argv)
{
	t_input	input;

	if (argc < 1 && !*argv[0])
		return (1);
	ft_printf("lem_in\n");
	ft_bzero(&input, sizeof(t_input));
	input.ant_count = -1;
	read_stdin(&parse_input, (void*)&input);
	if (!input.start || !input.end)
		error("missing start or end room");
	input.graph = new_graph(&input);
	if (!input.graph->start || !input.graph->end)
		error("bad input format (start or end commands hidden by duplicate rooms)");
	input.graph->start->start = 1;
	input.graph->end->end = 1;
	ft_printf("=== Graph ========\n");
	//ft_printf("start room: %s\nend room: %s\n", (char *)input.start->content, (char *)input.end->content);
	ft_printf("start node: %s\nend node: %s\n", input.graph->start->name, input.graph->end->name);
	ft_printf("==================\n");

	ft_printf("sizeof(t_node): %u\n", sizeof(t_node));

	ft_printf("=== graph traversal ===\n");
	// Traverse with each branch to find shortest path
	//graph_traversal(input.graph->start, NULL, 4);
	compute_pathes(input.graph->end, 0);
	//graph_traversal(input.graph->start, NULL, 4);
	ft_printf("=======================\n");
	dequeue(input.rooms);
	dequeue(input.connections);
	//ft_printf("%s\n", f.str);
	ft_printf("exit\n");
	return (0);
}
