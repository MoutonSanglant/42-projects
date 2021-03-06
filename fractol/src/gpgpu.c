/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpgpu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 17:48:25 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/21 10:42:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef FRACTOL_OPENCL

void	gpgpu_init(t_context *ctx)
{
	ft_bzero(&ctx->gpgpu, sizeof(t_gpgpu));
	cl_init(&ctx->gpgpu, ctx->canvas->width, ctx->canvas->height);
}

void	gpgpu_close(t_context *ctx)
{
	cl_close(&ctx->gpgpu);
}

#else

void	gpgpu_init(t_context *ctx)
{
	(void)ctx;
}

void	gpgpu_close(t_context *ctx)
{
	(void)ctx;
}

#endif
