/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   el.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reyvan-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:50:52 by reyvan-d          #+#    #+#             */
/*   Updated: 2016/10/05 17:05:47 by reyvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		key_hook(int key, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (key == 53)
		exit(1);
	else if (key == 69)
	{
		env->pos->zm *= 1.5;
		env->pos->off_x += 1 / env->pos->zm;
		env->pos->off_y += 1 / env->pos->zm;
	}
	else if (key == 78)
	{
		env->pos->zm /= 1.5;
		env->pos->off_x -= 1 / env->pos->zm;
		env->pos->off_y -= 1 / env->pos->zm;
	}
	check_pos(env);
	draw(env);
	return (0);
}

int		expose_hook(void *param)
{
	t_env	*env;

	env = (t_env*)param;
	check_pos(env);
	draw(env);
	return (0);
}

int		m_hook(int x, int y, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (env->op == 1 && env->cap_m)
	{
		env->pos->julia_x = (double)x / (double)env->win_wd;
		env->pos->julia_y = (double)y / (double)env->win_ht;
		if (env->pos->julia_x < 0)
			env->pos->julia_x = 0;
		else if (env->pos->julia_x > 1)
			env->pos->julia_x = 1;
		if (env->pos->julia_y < 0)
			env->pos->julia_y = 0;
		else if (env->pos->julia_y > 1)
			env->pos->julia_y = 1;
		check_pos(env);
		draw(env);
	}
	return (0);
}

void	check_pos(t_env *env)
{
	if (env->pos->zm < 1)
		env->pos->zm = 1;
	else if (env->pos->zm > 1000000)
		env->pos->zm = 1000000;
	if (env->pos->off_x < 0)
		env->pos->off_x = 0;
	else if (env->pos->off_x > 4 - .5 / env->pos->zm)
		env->pos->off_x = 4 - .5 / env->pos->zm;
	if (env->pos->off_y < 0)
		env->pos->off_y = 0;
	else if (env->pos->off_y > 4 - .5 / env->pos->zm)
		env->pos->off_y = 4 - .5 / env->pos->zm;
	env->pos->min_x = (-2.) + env->pos->off_x;
	env->pos->max_x = 4. / env->pos->zm + env->pos->min_x;
	env->pos->min_y = (-2.) + env->pos->off_y;
	env->pos->max_y = 4. / env->pos->zm + env->pos->min_y;
	if (env->pos->d < .1)
		env->pos->d = .1;
}

int		m_hook2(int key, int x, int y, void *param)
{
	static int	i;
	t_env		*env;

	i++;
	env = (t_env*)param;
	if (key == 1)
		env->cap_m = (env->cap_m) ? 0 : 1;
	else if (key == 4 && (i % 2) == 0)
	{
		env->pos->zm *= 1.5;
		env->pos->off_x += ((float)x / (float)(env->win_wd) * 2) / env->pos->zm;
		env->pos->off_y += ((float)y / (float)(env->win_ht) * 2) / env->pos->zm;
	}
	else if (key == 5 && (i % 2) == 0)
	{
		env->pos->zm /= 1.5;
		env->pos->off_x -= ((float)x / (float)(env->win_wd) * 2) /
			env->pos->zm;
		env->pos->off_y -= ((float)y / (float)(env->win_ht) * 2) /
			env->pos->zm;
	}
	check_pos(env);
	draw(env);
	return (0);
}
