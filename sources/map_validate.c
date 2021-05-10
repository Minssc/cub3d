/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:38:00 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/10 18:57:45 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		dfs_map_validate(t_map *map, t_byte *va, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->x + 2 || y >= map->y + 2 ||
		va[y * (map->x + 2) + x])
		return ;
	if (map_at(map, y - 1, x - 1) != '1' && map_at(map, y - 1, x - 1) != ' ')
	{
		free(va);
		va = 0;
		perror_exit("Invalid map (incomplete wall)");
	}
	if (map_at(map, y - 1, x - 1) == '1')
		return ;
	va[y * (map->x + 2) + x] = 1;
	dfs_map_validate(map, va, y + 0, x + 1);
	dfs_map_validate(map, va, y + 1, x + 1);
	dfs_map_validate(map, va, y + 1, x + 0);
	dfs_map_validate(map, va, y + 1, x - 1);
	dfs_map_validate(map, va, y + 0, x - 1);
	dfs_map_validate(map, va, y - 1, x - 1);
	dfs_map_validate(map, va, y - 1, x + 0);
	dfs_map_validate(map, va, y - 1, x + 1);
}

static void		dfs_segment(t_map *map, t_byte *va, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->x + 2 || y >= map->y + 2 ||
		va[y * (map->x + 2) + x])
		return ;
	va[y * (map->x + 2) + x] = 1;
	dfs_segment(map, va, y + 0, x + 1);
	dfs_segment(map, va, y + 1, x + 0);
	dfs_segment(map, va, y + 0, x - 1);
	dfs_segment(map, va, y - 1, x + 0);
}

static void		map_check_chunks(t_map *map, t_byte *va)
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
			if (!va[y * (map->x + 2) + x])
			{
				if (c++)
					perror_exit("Invalid map (multiple chunks found)");
				dfs_segment(map, va, y, x);
			}
		}
	}
}

static void		map_check_startpos(t_map *map, t_byte *va)
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
	t_byte		*va;

	y = -1;
	if (!(va = (t_byte *)ft_calloc((map->x + 2) * (map->y + 2),
													sizeof(t_byte))))
		perror_exit("calloc failed for *va");
	while (++y <= map->y + 1)
	{
		x = -1;
		while (++x <= map->x + 1)
			if (!va[y * (map->x + 2) + x] && map_at(map, y - 1, x - 1) == ' ')
				dfs_map_validate(map, va, y, x);
	}
	map_check_chunks(map, va);
	map_check_startpos(map, va);
	free(va);
}
