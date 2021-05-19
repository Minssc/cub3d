/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:55:47 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/19 21:29:31 by minsunki         ###   ########.fr       */
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
	int			tmp;

	if (!r->side)
		r->pwd = (r->map_p.x - r->pl_p.x + (1 - r->step.x) / 2) / r->ray.x;
	else
		r->pwd = (r->map_p.y - r->pl_p.y + (1 - r->step.y) / 2) / r->ray.y;
	r->l_len = (int)(res->y / r->pwd);
	r->l_start = -r->l_len / 2 + res->y / 2;
	r->l_end = r->l_len / 2 + res->y / 2;
	if (r->l_start < 0)
		r->l_start = 0;
	if (r->l_end >= res->y)
		r->l_end = res->y - 1;
	if (r->l_end < r->l_start)
	{
		tmp = r->l_start;
		r->l_start = r->l_end;
		r->l_end = tmp;
	}
}

static void		ray_dda(t_rend *r, t_res *res, t_map *map)
{
	while (1)
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
			break ;
	}
}

int				render(t_meta *meta)
{
	t_res		*res;
	t_rend		*r;
	int			x;

	res = &meta->cubd->res;
	r = &meta->rend;
	x = -1;
	mmlx_prep_img(meta->img, meta->cubd);
	while (++x < res->x)
	{
		r->td = (2 * x) / (double)res->x - 1;
		r->ray.x = r->pl_v.x + r->pane_v.x * r->td;
		r->ray.y = r->pl_v.y + r->pane_v.y * r->td;
		r->map_p = (t_pnt2){(int)r->pl_p.x, (int)r->pl_p.y};
		r->delta = (t_vec2){fabs(1 / r->ray.x), fabs(1 / r->ray.y)};
		set_step(r);
		ray_dda(r, &meta->cubd->res, &meta->cubd->map);
		perp_and_height(r, &meta->cubd->res);
		mmlx_draw_vline(meta->img, x, r->l_start, r->l_end - r->l_start,
									r->side ? 0x00FFFFFF : 0x00EEEEEE);
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img->obj, 0, 0);
	return (0);
}