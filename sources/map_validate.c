/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:38:00 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/07 20:42:31 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_byte	**g_va;

void			dfs_bdcheck(int ox, int cx, int cy)
{
	t_map		*map;

	map = &g_cubd->map;

}

void			map_validate(void)
{
	t_map		*map;
	int			x;
	int			y;
	
	map = &g_cubd->map;
	x = -1;
	y = 0;
	if (!(g_va = (t_byte **)ft_calloc(map->y, sizeof(t_byte *))))
		perror_exit("calloc failed for **g_va");
	
	while (++x < map->x)
		if (map->dat[0][x] == '1')
			break ;
	
}
