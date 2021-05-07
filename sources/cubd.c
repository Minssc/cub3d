/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 00:57:33 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/07 20:15:28 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cubd		*g_cubd;

int			cubd_init(void)
{
	if (!(g_cubd = ft_calloc(1, sizeof(t_cubd))))
		return (0);
	return (1);
}

void		cubd_destroy(void)
{
	int		i;

	i = -1;
	if (g_cubd->map.dat)
	{
		while (++i < g_cubd->map.y)
		{
			if (!g_cubd->map.dat[i])
				break ;
			free(g_cubd->map.dat[i]);
			g_cubd->map.dat[i] = 0;
		}
		free(g_cubd->map.dat);
		g_cubd->map.dat = 0;
	}
	if (g_cubd)
		free(g_cubd);
	g_cubd = 0;
}
