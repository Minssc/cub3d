/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:55:47 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/23 10:47:03 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

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
		r->pwd = (r->map_p.x - r->pl_p.x + (1 - r->step.x) / 2) / r->ray.x;
	else
		r->pwd = (r->map_p.y - r->pl_p.y + (1 - r->step.y) / 2) / r->ray.y;
	r->l_height = (int)(res->y / r->pwd);
	r->l_start = ft_maxi(0, -r->l_height / 2 + res->y / 2);
	r->l_len = ft_mini(res->y - 1, r->l_height);
}

static void		ray_dda(t_rend *r, t_res *res, t_map *map)
{
	while (1)
	{
		if (r->side_v.x < r->side_v.y)
		{
			r->side_v.x += r->delta.x;
			r->map_p.x += r->step.x;
			r->side = (r->step.x < 0 ? 3 : 1);
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

static void		dbg_info(t_meta *m)
{
static clock_t lc;
	t_rend *r = &m->rend;
	int i =0;
	char str[65535];

	sprintf(str, "pos: %.3lf %.3lf", r->pl_p.x, r->pl_p.y);
	mlx_string_put(m->mlx, m->win, 100, 50 + i++ * 20, 0x00FFFFFF, str);

	sprintf(str, "dir: %.3lf %.3lf", r->pl_v.x, r->pl_v.y);
	mlx_string_put(m->mlx, m->win, 100, 50 + i++ * 20, 0x00FFFFFF, str);


	sprintf(str, "Tdelta: %.5lf", (clock() - lc) / (double)CLOCKS_PER_SEC);
	mlx_string_put(m->mlx, m->win, 100, 50 + i++ * 20, 0x00FFFFFF, str);
	lc = clock();
}

int				render(t_meta *meta)
{
static clock_t tick;
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
		mmlx_draw_textured_line(meta, r, &meta->cubd->tex[r->side], x);
	}
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img->obj, 0, 0);
	dbg_info(meta);
	return (0);
}
