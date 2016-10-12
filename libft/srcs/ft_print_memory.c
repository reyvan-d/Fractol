/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 09:01:32 by exam              #+#    #+#             */
/*   Updated: 2016/08/20 09:51:07 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_dots(unsigned char *str, int k, int l)
{
	while (++k <= l)
	{
		if (str[k] < 32 || str[k] > 126)
			ft_putchar('.');
		else
			ft_putchar(str[k]);
	}
}

void		ft_print_memory(const void *addr, size_t size)
{
	size_t			k;
	size_t			l;
	unsigned char	*str;

	k = -1;
	str = (unsigned char *)addr;
	l = (size % 16 == 0) ? size : size + (16 - (size % 16));
	while (++k < l)
	{
		if (k < size)
		{
			if (str[k] < 16)
				ft_putchar('0');
			ft_print_hex(str[k]);
		}
		else
			write(1, "  ", 2);
		if (((k + 1) % 2) == 0)
			ft_putchar(' ');
		if ((k + 1) % 16 == 0)
		{
			(k < size) ? print_dots(str, k - 16, k) \
				: print_dots(str, (size - (size % 16) - 1), size - 1);
			ft_putchar('\n');
		}
	}
}
