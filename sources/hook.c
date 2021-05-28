/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:53:11 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 23:28:43 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			hook_destroy(void)
{
	mexit(0);
	return (0);
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
	return (0);
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
	return (0);
}

int			hook_think(t_meta *meta)
{
	pl_think(meta);
	render(meta);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img->obj, 0, 0);
	return (0);
}
