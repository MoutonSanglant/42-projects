/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 04:19:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/21 15:51:48 by tdefresn         ###   ########.fr       */
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

static void	print_room(t_room *room)
{
	//ft_printf("room: %s %i %i\n", room->name, room->x, room->y);
	ft_printf("%s %i %i\n", room->name, room->x, room->y);
}


static void	print_connection(t_connection *connection)
{
	//ft_printf("connection: %s-%s\n", connection->from, connection->to);
	ft_printf("%s-%s\n", connection->from, connection->to);
}


static void	print_anthill(t_parser *parser)
{
	t_queue		*queue;
	t_key		*key;

	queue = parser->queue;
	ft_printf("%i\n", parser->ants_count);
	while (queue)
	{
		key = (t_key *)queue->content;

		if (key->type & TYPE_COMMENT)
			ft_printf("%s\n", (char *)key->value);
		else if (key->type & TYPE_ROOM)
			print_room((t_room *)key->value);
		else if (key->type & TYPE_CONNECTION)
			print_connection((t_connection *)key->value);
		ft_memdel((void *)&key->value);
		ft_memdel((void *)&queue->content);
		ft_queuepop(&queue);
	}
	write(1, "\n", 1);
}

int main(void)
{
	t_parser	parser;
	t_graph		graph;

	ft_bzero(&graph, sizeof(t_graph));
	ft_bzero(&parser, sizeof(t_parser));
	parser.ants_count = -1;
	read_stdin(&parse_line, (void*)&parser);
	new_graph(&graph, &parser);
	print_anthill(&parser);
	graph.end->weight = -1;
	graph.end->state = STATE_END;
	graph.start->state = STATE_START;
	graph.ants_count = parser.ants_count;
	mark_all_path(&graph, graph.end, 0);
	resolve(&graph);
	return (0);
}
