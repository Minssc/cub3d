/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:38:00 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/09 20:25:11 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_cubd	*g_cubd;
static t_byte	*g_va;

void			dfs_fill(int cx, int cy)
{
	t_map		*map;

	map = &g_cubd->map;
	if (cx < 0 || cx >= map->x || cy < 0 || cy >= map->y ||
		g_va[cy * map->x + cx])
		return ;
	g_va[cy * map->x + cx] = 1;
	dfs_fill(cx + 1, cy);
	dfs_fill(cx, cy + 1);
	dfs_fill(cx - 1, cy);
	dfs_fill(cx, cy - 1);
}

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
/*
static int		map_check_chunks(void)
{
	t_map		*map;
	int			x;
	int			y;
	int			c;

	map = &g_cubd->map;
	y = -1;
	c = 0;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (map->dat[y][x] != ' ' && !g_va[y * map->x + x])
			{
				if (c++)
					return (1);
				dfs_segment(x, y);
			}
		}
	}
	return (0);
}
*/

static void	p_ga()
{
	t_map *map = &g_cubd->map;

	for(int i=0; i<map->y + 2; ++i){
		for(int j=0; j<map->x + 2; ++j){
			if (g_va[i*(map->x + 2) + j])
				printf("%c",g_va[i*(map->x + 2) + j] + '0');
			else
				printf(" ");
		}
		printf("\n");
	}
}
static t_byte	map_at(int y, int x)
{
	t_map		*map;

	map = &g_cubd->map;
	if (x < 0 || y < 0 || x >= map->x || y >= map->y)
		return ' ';
	return map->dat[y][x];
}

static void		dfs_map_validate(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->x + 2 || y >= map->y + 2 ||
		g_va[y * (map->x + 2) + x])
		return ;
	if (map_at(y - 1, x - 1) != '1' && map_at(y - 1, x - 1) != ' ')
	{
		free(g_va);
		g_va = 0;
		perror_exit("Invalid map (incomplete wall)");
	}
	if (map_at(y - 1, x - 1) == '1')
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
/*
static void		dfs_segment(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->x + 2 || y >= map->y + 2 ||
		g_va[y * (map->x + 2) + x])
		return ;
	if (map_at(y - 1, x - 1) == ' ')
	{
		free(g_va);
		g_va = 0;
		perror_exit("Invalid map (space inside map)");
	}
	g_va[y * (map->x + 2) + x] = 1;
	dfs_segment(map, x + 1, y + 0);
	dfs_segment(map, x + 0, y + 1);
	dfs_segment(map, x - 1, y + 0);
	dfs_segment(map, x + 0, y - 1);
}

static void		map_validate_internal(t_map *map)
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
				printf("%d %d\n\n", y, x);
				p_ga();
				if (c++)
					perror_exit("Invalid map (multiple chunks found)");
				dfs_segment(map, y, x);
			}
		}
	}
}
*/
static void		map_findSPos(t_map *map)
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
				if (t == 'N')
					map->sd = NORTH;
				else if (t == 'S')
					map->sd = SOUTH;
				else if (t == 'E')
					map->sd = EAST;
				else if (t == 'W')
					map->sd = WEST;
			}
		}
	}
	if (!map->sp)
		perror_exit("Invalid map (no start position)");
}

void			map_validate(void)
{
	t_map		*map;
	int			x;
	int			y;
	
	map = &g_cubd->map;
	y = -1;
	if (!(g_va = (t_byte *)ft_calloc((map->x + 2) * (map->y + 2),
													sizeof(t_byte))))
		perror_exit("calloc failed for *g_va");
	while (++y <= map->y + 1)
	{
		x = -1;
		while (++x <= map->x + 1)
			if (!g_va[y * (map->x + 2) + x] && map_at(y - 1, x - 1) == ' ')
				dfs_map_validate(map, y, x);
	}
	map_findSPos(map);
//	map_validate_internal(map);
//	printf("\n\n");
//	p_ga();
/*	
	printf("map size: %d x %d\n",map->y, map->x);
	if (!(g_va = (t_byte *)ft_calloc(map->x * map->y, sizeof(t_byte))))
		perror_exit("calloc failed for *g_va");
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (!g_va[y * map->x + x] && map->dat[y][x] == ' ')
			{
				printf("check @ %d %d\n",y, x);
				fflush(stdout);
				dfs_map_validate(map, y, x);
			}
		}
	}

*/	
		/*
	if (map_check_chunks())
		perror_exit("Invalid map (multiple chunks found)");
	while (++x < map->x)
		if (map->dat[0][x] == '1')
			break ;
	g_va[x] = 1;
	dfs_bdcheck(x, x + 1, 0);

	
	if (g_va[x] != 2)
		perror_exit("Invalid map (not surrounded)");
	*/
}
