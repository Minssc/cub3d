/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 23:40:52 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 15:57:26 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		pl_move(t_meta *meta, double speed)
{
	const double	lim = 0.001;
	const t_map		*m = &meta->cubd->map;
	t_rend			*r;
	int				x;
	int				y;

	r = &meta->rend;
	x = (int)(r->pl_p.x + r->pl_v.x * speed);
	y = (int)(r->pl_p.y + r->pl_v.y * speed);
	if (m->dat[y][x] != '1')
	{
		r->pl_p.x += r->pl_v.x * speed;
		r->pl_p.y += r->pl_v.y * speed;
		return ;
	}
	if (x != (int)r->pl_p.x && m->dat[(int)r->pl_p.y][x] == '1')
		r->pl_p.x = (r->pl_v.x * speed < 0 ? (int)r->pl_p.x + lim : x - lim);
	else
		r->pl_p.x += r->pl_v.x * speed;
	if (y != (int)r->pl_p.y && m->dat[y][(int)r->pl_p.x] == '1')
		r->pl_p.y = (r->pl_v.y * speed < 0 ? (int)r->pl_p.y + lim : y - lim);
	else
		r->pl_p.y += r->pl_v.y * speed;
}

static void		pl_strafe(t_meta *meta, double speed)
{
	const double	lim = 0.001;
	const t_map		*m = &meta->cubd->map;
	t_rend			*r;
	int				x;
	int				y;

	r = &meta->rend;
	x = (int)(r->pl_p.x + r->pl_v.y * speed);
	y = (int)(r->pl_p.y - r->pl_v.x * speed);
	if (m->dat[y][x] != '1')
	{
		r->pl_p.x += r->pl_v.y * speed;
		r->pl_p.y -= r->pl_v.x * speed;
		return ;
	}
	if (x != (int)r->pl_p.x && m->dat[(int)r->pl_p.y][x] == '1')
		r->pl_p.x = (r->pl_v.y * speed < 0 ? (int)r->pl_p.x + lim : x - lim);
	else
		r->pl_p.x += r->pl_v.y * speed;
	if (y != (int)r->pl_p.y && m->dat[y][(int)r->pl_p.x] == '1')
		r->pl_p.y = (r->pl_v.x * speed > 0 ? (int)r->pl_p.y + lim : y - lim);
	else
		r->pl_p.y -= r->pl_v.x * speed;
}

void			pl_rotate(t_rend *r, double deg)
{
	double		sinv;
	double		cosv;
	double		tmp;

	deg *= RADIAN;
	sinv = sin(deg);
	cosv = cos(deg);
	tmp = r->pl_v.x;
	r->pl_v.x = r->pl_v.x * cosv - r->pl_v.y * sinv;
	r->pl_v.y = tmp * sinv + r->pl_v.y * cosv;
	tmp = r->pane_v.x;
	r->pane_v.x = r->pane_v.x * cosv - r->pane_v.y * sinv;
	r->pane_v.y = tmp * sinv + r->pane_v.y * cosv;
}

void			pl_init(t_rend *r, t_map *m)
{
	r->pl_p = (t_vec2){m->sp % m->x + 0.5, m->sp / m->x + 0.5};
	r->pl_v = (t_vec2){0.0, -1.0};
	r->pane_v = (t_vec2){0.66, 0.0};
	pl_rotate(r, 90.0 * m->sd);
}

void			pl_think(t_meta *meta)
{
	const t_kb	*kb = meta->keys;

	if (kb->w ^ kb->s)
		pl_move(meta, (kb->w ? 0.02 : -0.02));
	if (kb->a ^ kb->d)
		pl_strafe(meta, (kb->a ? 0.02 : -0.02));
	if (kb->la ^ kb->ra)
		pl_rotate(&meta->rend, (kb->la ? -0.6 : 0.6));
}
