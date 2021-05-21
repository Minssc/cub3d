/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:58:50 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/21 19:48:08 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				main(int argc, char *argv[])
{
	t_meta		*meta;

	if (argc != 2 && argc != 3)
	{
		ft_putstr_fd("Usage: ./cub3D cub_file [--save]\n", 1);
		return (1);
	}
	meta = meta_init();
	cub_parse(meta, argv[1]);
	map_validate(&meta->cubd->map);
	mmlx_init(meta);
	pl_init(&meta->rend, &meta->cubd->map);
	mlx_hook(meta->win, 2, 1L << 0, hook_keypress, meta);
	mlx_hook(meta->win, 3, 1L << 1, hook_keyrelease, meta);
	mlx_hook(meta->win, 17, 0L, hook_destroy, meta);
	mlx_loop_hook(meta->mlx, hook_think, meta);
	mlx_loop(meta->mlx);
	return (0);
}
