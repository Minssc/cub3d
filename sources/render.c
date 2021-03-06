/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:55:47 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 23:55:52 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_step(t_rend *r)
{
	r->step.x = (r->ray.x < 0 ? -1 : 1);
	r->step.y = (r->ray.y < 0 ? -1 : 1);
	if (r->ray.x < 0)
		r->side_v.x = (r->pl_p.x - r->map_p.x) * r->delta.x;
	else
		r->side_v.x = (r->map_p.x + 1.0 - r->pl_p.x) * r->delta.x;
	if (r->ray.y < 0)
		r->side_v.y = (r->pl_p.y - r->map_p.y) * r->delta.y;
	else
		r->side_v.y = (r->map_p.y + 1.0 - r->pl_p.y) * r->delta.y;
}

static void		perp_and_height(t_rend *r, t_res *res)
{
	if (r->side == 1 || r->side == 3)
		r->pwd = (r->map_p.x - r->pl_p.x + ((1 - r->step.x) >> 1)) / r->ray.x;
	else
		r->pwd = (r->map_p.y - r->pl_p.y + ((1 - r->step.y) >> 1)) / r->ray.y;
	r->l_height = (int)(res->y / r->pwd);
	r->l_start = ft_maxi(0, -(r->l_height >> 1) + (res->y >> 1));
	r->l_len = ft_mini(res->y - 1, r->l_height);
	r->l_end = r->l_start + r->l_len;
}

static void		ray_dda(t_rend *r, t_map *map)
{
	while (1)
	{
		if (r->side_v.x < r->side_v.y)
		{
			r->side_v.x += r->delta.x;
			r->map_p.x += r->step.x;
			r->side = (r->step.x < 0 ? 1 : 3);
		}
		else
		{
			r->side_v.y += r->delta.y;
			r->map_p.y += r->step.y;
			r->side = (r->step.y < 0 ? 2 : 0);
		}
		if (map->dat[r->map_p.y][r->map_p.x] == '1')
			break ;
	}
}

int				render(t_meta *meta)
{
	const t_res	*res = &meta->cubd->res;
	t_cubd		*cubd;
	t_rend		*r;
	int			x;

	r = &meta->rend;
	cubd = meta->cubd;
	x = -1;
	mmlx_prep_img(meta->img, cubd);
	while (++x < res->x)
	{
		r->td = (2 * x) / (double)res->x - 1;
		r->ray.x = r->pl_v.x + r->pane_v.x * r->td;
		r->ray.y = r->pl_v.y + r->pane_v.y * r->td;
		r->map_p = (t_pnt2){(int)r->pl_p.x, (int)r->pl_p.y};
		r->delta = (t_vec2){fabs(1 / r->ray.x), fabs(1 / r->ray.y)};
		set_step(r);
		ray_dda(r, &cubd->map);
		perp_and_height(r, &cubd->res);
		mmlx_draw_textured_line(meta, r, &cubd->tex[r->side], x);
	}
	return (0);
}
