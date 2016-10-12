/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BS.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reyvan-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 11:36:58 by reyvan-d          #+#    #+#             */
/*   Updated: 2016/10/05 17:26:03 by reyvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static int		col_get(float i, float max_iter)
{
	if (max_iter == i)
		return (0);
	return ((int)(0xFF0000 * i / max_iter) / 0x010000 * 0x010000);
}

int				bs(t_env *env, t_cx *cpx1, t_cx *cpx2, t_coord *pt)
{
	int		max_iter;
	int		i;

	max_iter = 50 * env->pos->d;
	i = 0;
	cpx1->r = 0;
	cpx1->i = 0;
	while (i < max_iter && (cpx1->r * cpx1->r + cpx1->i * cpx1->i) < 4)
	{
		if (cpx1->r < 0)
			cpx2->r = cpx1->r * -1;
		else
			cpx2->r = cpx1->r;
		if (cpx1->i < 0)
			cpx2->i = cpx1->i * -1;
		else
			cpx2->i = cpx1->i;
		cpx1->r = cpx2->r * cpx2->r - cpx2->i * cpx2->i + pt->x;
		cpx1->i = 2. * cpx2->r * cpx2->i + pt->y / 1.777777;
		i++;
	}
	return (col_get(i, max_iter));
}
