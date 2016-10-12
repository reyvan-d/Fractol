/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reyvan-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 11:19:48 by reyvan-d          #+#    #+#             */
/*   Updated: 2016/10/03 15:50:19 by reyvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static	int	col_get(double i, double max_iter)
{
	if (max_iter == i)
		return (0);
	if (i < max_iter / 2)
		return (0x0000FF * i / (max_iter / 2));
	return (0x0000FF + 0xFFFF00 * i / max_iter);
}

int			julia(t_env *env, t_cx *cpx1, t_cx *cpx2, t_coord *pt)
{
	int		max_iter;
	int		i;

	max_iter = 100 * env->pos->d;
	i = 0;
	cpx1->r = pt->x;
	cpx1->i = pt->y;
	while (i < max_iter && (cpx1->r * cpx1->r + cpx1->i * cpx1->i) < 4)
	{
		cpx2->r = cpx1->r;
		cpx2->i = cpx1->i;
		cpx1->r = cpx2->r * cpx2->r - cpx2->i * cpx2->i - 0.7
			- env->pos->julia_x / 10.0;
		cpx1->i = 2 * cpx2->r * cpx2->i + 0.27 + env->pos->julia_y / 10.0;
		i++;
	}
	return (col_get(i, max_iter));
}
