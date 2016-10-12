/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reyvan-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/02 14:28:13 by reyvan-d          #+#    #+#             */
/*   Updated: 2016/10/03 12:46:18 by reyvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		err_quit(char *str)
{
	ft_putstr(str);
	exit(1);
}

static void	win_init(t_env *env)
{
	int		temp;

	if (!(env->win = malloc(sizeof(*(env->win)))))
		err_quit("Failed to allocate memory to struct");
	env->win_wd = 800;
	env->win_ht = 600;
	if (!(env->mlx = mlx_init()))
		err_quit("Failed to init mlx");
	if (!(env->win = mlx_new_window(env->mlx
					, env->win_wd, env->win_ht
					, "fract'ol")))
		err_quit("Failed to create window");
	env->bpp = 3 * 8;
	env->endian = 1;
	temp = env->win_wd * env->bpp / 8;
	if (!(env->img = mlx_new_image(env->mlx
					, env->win_wd, env->win_ht)))
		err_quit("Failed to create image");
	if (!(env->data = mlx_get_data_addr(env->img
					, &(env->bpp), &temp
					, &(env->endian))))
		err_quit("Failed to get image data");
}

void		init(t_env *env, char **av)
{
	win_init(env);
	if (!(env->pos = malloc(sizeof(*(env->pos)))))
		err_quit("Failed to initialize position");
	env->pos->zm = 1.;
	env->pos->d = 1;
	env->pos->off_x = 0.;
	env->pos->off_y = 0.;
	env->pos->julia_x = 0;
	env->pos->julia_y = 0;
	if (ft_strcmp(av[1], "Julia") == 0)
		env->op = 1;
	else if (ft_strcmp(av[1], "MBrot") == 0)
		env->op = 2;
	else if (ft_strcmp(av[1], "BS") == 0)
		env->op = 3;
	else
		err_quit("Usage: ./fractal [Julia, MBrot, BS]\n");
}

int			main(int ac, char **av)
{
	t_env		*env;

	if (ac < 2)
		err_quit("Usage: ./fractol [Julia, MBrot, BS]\n");
	if (!(env = malloc(sizeof(*env))))
		err_quit("Failed to initialize env");
	init(env, av);
	mlx_key_hook(env->win, &key_hook, env);
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_hook(env->win, 6, (1 << 6), &m_hook, env);
	mlx_mouse_hook(env->win, &m_hook2, env);
	mlx_hook(env->win, 17, 0L, &close_window, env);
	mlx_loop(env->mlx);
	return (0);
}

int			close_window(t_env *env)
{
	free(env);
	exit(0);
}
