/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 23:49:25 by mouton            #+#    #+#             */
/*   Updated: 2017/09/12 22:32:49 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "options.h"
#include "errors.h"

static int	fallback(const char *arg, void *user_data)
{
	t_context *context = (t_context *)user_data;

	ft_printf("Read value: %s\nwidth: %i\nheight: %i\n", arg, context->window.size.x, context->window.size.y);
	return (1);
}

static int	help(const char *arg, void *user_data)
{
	(void)arg;
	(void)user_data;
	error(ERRNO_USAGE, NULL);
	return (0);
}

static void	set_options_data(t_option *options, t_context *context)
{
	options[0].user = context;
	options[1].user = NULL;
	options[2].user = &context->window.size.x;
	options[3].user = &context->window.size.y;
}

int		get_arguments(int argc, const char **argv, t_context *context)
{
	static t_option options[] =
	{
		{ .name = NULL, .token = NULL, .fn = &fallback, .user = NULL, .skip = 0 },
		{ .name = "help", .token = "H", .fn = &help, .user = NULL, .skip = 0 },
		{ .name = "width", .token = "w", .fn = &parse_argument_width, .user = NULL, .skip = 1 },
		{ .name = "height", .token = "h", .fn = &parse_argument_height, .user = NULL, .skip = 1 },
		{ .token = NULL, .name = NULL }
	};

	set_options_data(options, context);
	return (parse_options(argc - 1, &argv[1], options));
}
