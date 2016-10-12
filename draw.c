/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reyvan-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 17:06:23 by reyvan-d          #+#    #+#             */
/*   Updated: 2016/10/05 17:06:25 by reyvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		put_pxl(t_env *env, int x, int y, unsigned int colour)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (colour & 0xFF0000) >> 16;
	g = (colour & 0x00FF00) >> 8;
	b = (colour & 0x0000FF);
	if (x >= 0 && x <= env->win_wd && y >= 0 && y <= env->win_ht)
	{
		env->data[y * env->win_wd * env->bpp / 8 + env->bpp / 8 * x] = b;
		env->data[y * env->win_wd * env->bpp / 8 + env->bpp / 8 * x + 1] = g;
		env->data[y * env->win_wd * env->bpp / 8 + env->bpp / 8 * x + 2] = r;
	}
}

static void	draw_pxl(t_env *env, t_cx *cpx1, t_cx *cpx2, t_coord *pt)
{
	int		colour;

	if (env->op == 1 || env->op == 2 || env->op == 3)
	{
		colour = 0;
		if (env->op == 1)
			colour = julia(env, cpx1, cpx2, pt);
		else if (env->op == 2)
			colour = m_brot(env, cpx1, cpx2, pt);
		else if (env->op == 3)
			colour = bs(env, cpx1, cpx2, pt);
		put_pxl(env, (pt->x - env->pos->min_x) / (env->pos->max_x -
				env->pos->min_x)
				* env->win_wd, (pt->y - env->pos->min_y) / (env->pos->max_y
				- env->pos->min_y) * env->win_ht, colour);
	}
}

static void	render(t_env *env, t_cx *cpx1, t_cx *cpx2, t_coord *pt)
{
	env->pos->y = env->pos->min_y;
	while (env->pos->y <= env->pos->max_y)
	{
		env->pos->x = env->pos->min_x;
		while (env->pos->x <= env->pos->max_x)
		{
			pt->x = env->pos->x;
			pt->y = env->pos->y;
			draw_pxl(env, cpx1, cpx2, pt);
			env->pos->x += (env->pos->max_x - env->pos->min_x)
				/ env->win_wd / 1.1;
		}
		env->pos->y += (env->pos->max_y - env->pos->min_y)
				/ env->win_ht / 1.1;
	}
}

void		draw(t_env *env)
{
	t_cx	*cpx1;
	t_cx	*cpx2;
	t_coord	*pt;

	if (!(pt = malloc(sizeof(*pt))))
		return ;
	if (!(cpx1 = malloc(sizeof(*pt))))
	{
		free(pt);
		return ;
	}
	if (!(cpx2 = malloc(sizeof(*cpx2))))
	{
		free(pt);
		free(cpx1);
		return ;
	}
	render(env, cpx1, cpx2, pt);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	free(pt);
	free(cpx1);
	free(cpx2);
}
