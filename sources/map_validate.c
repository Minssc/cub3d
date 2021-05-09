/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:38:00 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/09 20:57:03 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_byte	*g_va;

static void		dfs_map_validate(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->x + 2 || y >= map->y + 2 ||
		g_va[y * (map->x + 2) + x])
		return ;
	if (map_at(map, y - 1, x - 1) != '1' && map_at(map, y - 1, x - 1) != ' ')
	{
		free(g_va);
		g_va = 0;
		perror_exit("Invalid map (incomplete wall)");
	}
	if (map_at(map, y - 1, x - 1) == '1')
		return ;
	g_va[y * (map->x + 2) + x] = 1;
	dfs_map_validate(map, y + 0, x + 1);
	dfs_map_validate(map, y + 1, x + 1);
	dfs_map_validate(map, y + 1, x + 0);
	dfs_map_validate(map, y + 1, x - 1);
	dfs_map_validate(map, y + 0, x - 1);
	dfs_map_validate(map, y - 1, x - 1);
	dfs_map_validate(map, y - 1, x + 0);
	dfs_map_validate(map, y - 1, x + 1);
}

static void		dfs_segment(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->x + 2 || y >= map->y + 2 ||
		g_va[y * (map->x + 2) + x])
		return ;
	g_va[y * (map->x + 2) + x] = 1;
	dfs_segment(map, y + 0, x + 1);
	dfs_segment(map, y + 1, x + 0);
	dfs_segment(map, y + 0, x - 1);
	dfs_segment(map, y - 1, x + 0);
}

static void		map_check_chunks(t_map *map)
{
	int			x;
	int			y;
	int			c;

	c = 0;
	y = -1;
	while (++y <= map->y + 1)
	{
		x = -1;
		while (++x <= map->x + 1)
		{
			if (!g_va[y * (map->x + 2) + x])
			{
				if (c++)
					perror_exit("Invalid map (multiple chunks found)");
				dfs_segment(map, y, x);
			}
		}
	}
}

static void		map_check_startpos(t_map *map)
{
	int			y;
	int			x;
	int			t;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			t = map->dat[y][x];
			if (t == 'N' || t == 'S' || t == 'E' || t == 'W')
			{
				if (map->sp)
					perror_exit("Invalid map (multiple start pos)");
				map->sp = (y * map->x + x);
				map->sd = map_char_to_dir(t);
			}
		}
	}
	if (!map->sp)
		perror_exit("Invalid map (no start position)");
}

void			map_validate(t_map *map)
{
	int			x;
	int			y;

	y = -1;
	if (!(g_va = (t_byte *)ft_calloc((map->x + 2) * (map->y + 2),
													sizeof(t_byte))))
		perror_exit("calloc failed for *g_va");
	while (++y <= map->y + 1)
	{
		x = -1;
		while (++x <= map->x + 1)
			if (!g_va[y * (map->x + 2) + x] && map_at(map, y - 1, x - 1) == ' ')
				dfs_map_validate(map, y, x);
	}
	map_check_chunks(map);
	map_check_startpos(map);
	free(g_va);
}
