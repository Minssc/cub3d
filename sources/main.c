/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:58:50 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/10 21:23:24 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	esc keycode: 	65307
	wasd:			119 97 115 100
	ctrl:			65513
	space:			32
	shift:			65505
*/

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
	cub_parse(argv[1]);
	map_validate(&meta->cubd->map);
	mmlx_init(meta);
	mlx_loop_hook(meta->mlx, render, meta);
	mlx_loop(meta->mlx);
//	meta->mlx = mmlx_init();

//	meta_destroy();

	/*
	if (argc == 3 && argv[2][0] == '-' && argv[2][1] == '-' &&
		argv[2][2] == 's' && argv[2][3] == 'a' && argv[2][4] == 'v' &&
		argv[2][5] == 'e' && argv[2][6] == '\0')
		//--SAVE
	*/

	//cubd_destroy(&meta->cubd);
	return (0);
}

/*
void		mmlx_pixel_put(t_data *dat, int x, int y, int col)
{
	char	*dst;

	dst = dat->addr + (y * dat->line_length + x * (dat->bpp / 8));
	*(unsigned int*)dst = col;
}

int			key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook! keycode: %d\n", keycode);
}

int			loop_hook(void *par)
{
	t_data	img;
	t_vars	*vars;
	static	int	lol;

	vars = (t_vars*)par;
	img.img = mlx_new_image(vars->mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	for(int i=0; i<800; ++i)
		mmlx_pixel_put(&img, lol, i, 0x00FF0000);
	lol++;
	lol %= 800;
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	mlx_destroy_image(vars->mlx, img.img);
}

int			main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 800, "Hello world!");

	img.img = mlx_new_image(vars.mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	for(int i=0; i<800; ++i)
		mmlx_pixel_put(&img, 100, i, 0x00FFFFFF);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);	
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);

	mlx_loop(vars.mlx);
	return (0);
}
*/
