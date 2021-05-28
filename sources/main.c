/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:58:50 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 23:26:38 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		print_usage(void)
{
	ft_putstr_fd("Usage: ./cub3D cub_file.cub\n", 1);
	exit(1);
}

static void		cub3d_start(t_meta *meta)
{
	mmlx_window_init(meta);
	mlx_hook(meta->win, 2, 1L << 0, hook_keypress, meta);
	mlx_hook(meta->win, 3, 1L << 1, hook_keyrelease, meta);
	mlx_hook(meta->win, 17, 0, hook_destroy, meta);
	mlx_loop_hook(meta->mlx, hook_think, meta);
	mlx_loop(meta->mlx);
}

int				main(int argc, char *argv[])
{
	t_meta		*meta;

	if (argc != 2)
		print_usage();
	if (argc == 2 && (ft_strlen(argv[1]) < 5 || ft_strncmp(argv[1] +
										ft_strlen(argv[1]) - 4, ".cub", 4)))
		print_usage();
	meta = meta_init();
	cub_parse(meta, meta->cubd, argv[1]);
	mmlx_prep_framebuffer(meta);
	map_validate(&meta->cubd->map);
	pl_init(&meta->rend, &meta->cubd->map);
	cub3d_start(meta);
	return (0);
}
