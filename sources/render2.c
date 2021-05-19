/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:28:56 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/19 00:01:27 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ray_dda(t_rend *r, t_res *res, t_map *map)
{
	while (!r->hit)
	{
		if (r->side_v.x < r->side_v.y)
		{
			r->side_v.x += r->delta.x;
			r->map_p.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_v.y += r->delta.y;
			r->map_p.y += r->step.y;
			r->side = 1;
		}
		if (map->dat[r->map_p.y][r->map_p.x] == '1')
			r->hit = 1;
	}
}

void			render_init(t_rend *r, t_cubd *cubd)
{
	t_map		*map;

	map = &cubd->map;
	r->pl_p = VEC2(map->sp % map->x + 0.5, map->sp / map->x + 0.5);
	r->pl_v = VEC2(0.0, -1.0);
	r->pane_v = VEC2(0.66, 0.0);
	pl_rotate(r, 90.0 * map->sd);
}
