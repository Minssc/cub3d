/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_util_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 20:38:13 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 15:57:07 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_byte			map_at(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->x || y >= map->y)
		return (' ');
	return (map->dat[y][x]);
}

t_byte			map_char_to_dir(t_byte c)
{
	if (c == 'N')
		return (NORTH);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'E')
		return (EAST);
	else if (c == 'W')
		return (WEST);
}
