/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 04:19:43 by tdefresn          #+#    #+#             */
/*   Updated: 2017/01/19 16:50:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Definitions:
** ------------
** #					-> commentaire
** ##					-> commande
** [a-Z]* [0-9]* [0-9]*	-> salle x y
** [a-Z]*-[0-9]*		-> liaison salle-salle
** L					-> reservé (erreur parsing)
** 'erreur ou vide'		-> fin acquisition (exécution programme)
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
** Nombre max fourmi / salle: 1
** Nombre max fourmi START / END: INT_MAX
** Les fourmis commencent toutes sur START
**
** Exemple (output):
** -----------------
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

static void	print_room(t_room *room, t_graph *graph)
{
	if (graph->flags & FLAG_COLORS)
		ft_printf("\033[33m");
	ft_printf("%s %i %i\n", room->name, room->x, room->y);
}

static void	print_connection(t_connection *connection, t_graph *graph)
{
	if (graph->flags & FLAG_COLORS)
		ft_printf("\033[35m");
	ft_printf("%s-%s\n", connection->from, connection->to);
	ft_memdel((void *)&connection->from);
	ft_memdel((void *)&connection->to);
}

static void	print_anthill(t_lemin_parser *parser, t_graph *graph)
{
	t_queue		*queue;
	t_key		*key;

	queue = parser->queue;
	ft_printf("%i\n", parser->ants_count);
	while (queue)
	{
		key = (t_key *)queue->content;
		if (graph->flags & FLAG_COLORS)
			ft_printf("\033[32m");
		if (key->type & TYPE_COMMENT)
			ft_printf("%s\n", (char *)key->value);
		else if (key->type & TYPE_ROOM)
			print_room((t_room *)key->value, graph);
		else if (key->type & TYPE_CONNECTION)
			print_connection((t_connection *)key->value, graph);
		ft_memdel((void *)&key->value);
		ft_memdel((void *)&queue->content);
		ft_queuepop(&queue);
	}
	if (graph->flags & FLAG_COLORS)
		ft_printf("\033[0m");
	write(1, "\n", 1);
}

int			main(int argc, char **argv)
{
	t_lemin_parser	parser;
	t_graph			graph;

	ft_bzero(&graph, sizeof(t_graph));
	ft_bzero(&parser, sizeof(t_lemin_parser));
	if (argc > 1)
		parse_arguments(argc, argv, &graph);
	parser.ants_count = -1;
	read_stdin(&parse_line, (void*)&parser);
	if (parser.ants_count < 1)
		error(ERR_INVALID_ANT_NUMBER);
	new_graph(&graph, &parser);
	graph.end->weight = 0;
	graph.end->state = STATE_END;
	graph.start->state = STATE_START;
	graph.start->weight = INT_MAX;
	graph.ants_count = parser.ants_count;
	mark_all_path(graph.end, 0, &graph, graph.end->links_count);
	if (graph.start->weight == INT_MAX)
		error(ERR_NO_LINK);
	graph.start->weight = INT_MAX;
	graph.start->state = STATE_START;
	print_anthill(&parser, &graph);
	resolve(&graph);
	return (0);
}
