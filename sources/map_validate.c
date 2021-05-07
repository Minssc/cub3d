/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:38:00 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/08 00:04:41 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_cubd	*g_cubd;
static t_byte	*g_va;

void			dfs_bdcheck(int ox, int cx, int cy)
{
	t_map		*map;

	map = &g_cubd->map;
	if (!cy && cx == ox)
	{
		g_va[ox] = 2;
		return ;
	}
	if (cx < 0 || cx >= map->x || cy < 0 || cy >= map->y ||
		g_va[cy * map->x + cx] || map->dat[cy][cx] != '1')
		return ;
	g_va[cy * map->x + cx] = 1;
	dfs_bdcheck(ox, cx + 1, cy);
	dfs_bdcheck(ox, cx, cy + 1);
	dfs_bdcheck(ox, cx - 1, cy);
	dfs_bdcheck(ox, cx, cy - 1);
}

void			map_validate(void)
{
	t_map		*map;
	int			x;
	int			y;
	
	map = &g_cubd->map;
	x = -1;
	y = 0;
	if (!(g_va = (t_byte *)ft_calloc(map->x * map->y, sizeof(t_byte))))
		perror_exit("calloc failed for *g_va");
	
	while (++x < map->x)
		if (map->dat[0][x] == '1')
			break ;
	g_va[x] = 1;
	dfs_bdcheck(x, x + 1, 0);
	for(int i=0; i<map->y; ++i){
		for(int j=0; j<map->x; ++j){
			if (g_va[i*map->x + j])
				printf("%c",g_va[i*map->x + j] + '0');
			else
				printf(" ");
		}
		printf("\n");
	}
	if (g_va[x] != 2)
		perror_exit("Invalid map (not surrounded)");
}
