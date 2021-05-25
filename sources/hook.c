/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:53:11 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/25 19:23:51 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			hook_destroy(t_meta *meta)
{
	mexit(0);
}

int			hook_keypress(int kc, t_meta *meta)
{
	if (kc == KC_ESC)
		mexit(0);
	else if (kc == KC_W)
		meta->keys->w = 1;
	else if (kc == KC_A)
		meta->keys->a = 1;
	else if (kc == KC_S)
		meta->keys->s = 1;
	else if (kc == KC_D)
		meta->keys->d = 1;
	else if (kc == KC_LA)
		meta->keys->la = 1;
	else if (kc == KC_RA)
		meta->keys->ra = 1;
}

int			hook_keyrelease(int kc, t_meta *meta)
{
	if (kc == KC_W)
		meta->keys->w = 0;
	else if (kc == KC_A)
		meta->keys->a = 0;
	else if (kc == KC_S)
		meta->keys->s = 0;
	else if (kc == KC_D)
		meta->keys->d = 0;
	else if (kc == KC_LA)
		meta->keys->la = 0;
	else if (kc == KC_RA)
		meta->keys->ra = 0;
}

static void     dbg_info(t_meta *m)
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

int			hook_think(t_meta *meta)
{
	pl_think(meta);
	render(meta);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img->obj, 0, 0);
	dbg_info(meta);
}
