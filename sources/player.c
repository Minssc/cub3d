/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 23:40:52 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/19 21:33:49 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		pl_move(t_meta *meta, double speed)
{
	t_rend		*r;
	t_map		*m;
	int			x;
	int			y;

	r = &meta->rend;
	m = &meta->cubd->map;
	x = (int)(r->pl_p.x + r->pl_v.x * speed);
	y = (int)(r->pl_p.y + r->pl_v.y * speed);
	if (m->dat[y][x] == '1')
		return ;
	r->pl_p.x += r->pl_v.x * speed;
	r->pl_p.y += r->pl_v.y * speed;
}

void			pl_rotate(t_rend *r, double deg)
{
	double		sinv;
	double		cosv;

	deg *= RADIAN;
	sinv = sin(deg);
	cosv = cos(deg);
	r->pl_v.x = r->pl_v.x * cosv - r->pl_v.y * sinv;
	r->pl_v.y = r->pl_v.x * sinv + r->pl_v.y * cosv;
	r->pane_v.x = r->pane_v.x * cosv - r->pane_v.y * sinv;
	r->pane_v.y = r->pane_v.x * sinv + r->pane_v.y * cosv;
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

	if (kb->w && !kb->s)
		pl_move(meta, 0.01);
	else if (!kb->w && kb->s)
		pl_move(meta, -0.01);
	if (kb->d && !kb->a)
		pl_rotate(&meta->rend, 0.4);
	else if (!kb->d && kb->a)
		pl_rotate(&meta->rend, -0.4);
}
