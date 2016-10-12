/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MBrot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reyvan-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 11:35:52 by reyvan-d          #+#    #+#             */
/*   Updated: 2016/10/03 11:36:40 by reyvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static int	col_get(double i, double max_iter)
{
	if (max_iter == i)
		return (0);
	if (i < max_iter)
		return (0x0000FF * i / max_iter);
	return (0x0000FF + 0xFFFF00 * i / max_iter / 1.5);
}

int			m_brot(t_env *env, t_cx *cpx1, t_cx *cpx2, t_coord *pt)
{
	int		max_iter;
	int		i;

	max_iter = 40 * env->pos->d;
	i = 0;
	cpx1->r = 0;
	cpx1->i = 0;
	while (i < max_iter && (cpx1->r * cpx1->r + cpx1->i * cpx1->i) < 4)
	{
		cpx2->r = cpx1->r;
		cpx2->i = cpx1->i;
		cpx1->r = cpx2->r * cpx2->r - cpx2->i * cpx2->i + pt->x;
		cpx1->i = 2. * cpx2->r * cpx2->i + pt->y / 1.777777;
		i++;
	}
	return (col_get(i, max_iter));
}
