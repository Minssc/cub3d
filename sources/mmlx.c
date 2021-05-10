/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 23:54:37 by minsunki          #+#    #+#             */
/*   Upimged: 2021/05/10 19:19:17 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			mmlx_init(t_meta *meta)
{
	const t_res	*res = &meta->cubd->res;

	meta->mlx = mlx_init();
	meta->win = mlx_new_window(meta->mlx, res->x, res->y, "cub3D");
	meta->img->obj = mlx_new_image(meta->mlx, res->x, res->y);
	meta->img->addr = mlx_get_data_addr(meta->img->obj, &meta->img->bpp,
										&meta->img->llen, &meta->img->endi);
	
/*
	mlx->obj = mlx_init();
	mlx->win = mlx_new_window(mlx->obj, res->x, res->y, "cub3D");
	mlx->img->ptr = mlx_new_image(mlx->obj, res->x, res->y);
	mlx->img->addr = mlx_get_data_addr(mlx->img->ptr, &mlx->img->bpp,
										&mlx->img->llen, &mlx->img->endi);
	return (mlx);
	*/
/*
	t_res		*res;

	res = &g_cubd->res;
	if (!(ret = (t_mlx *)malloc(sizeof(t_mlx))))
		perror_exit("Malloc failed @ mmlx_init");
	ret->obj = mlx_init();
	ret->win = mlx_new_window(ret->obj, res->x, res->y, "cub3D");
	ret->frame = mlx_new_image(ret->obj, 
	return (ret);
	*/
}

void			mmlx_pixel_put(t_img *img, int x, int y, t_argb col)
{
	char		*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp >> 3));
	*(t_argb *)dst = col;
}

void			mmlx_draw_vline(t_img *img, int x, int y, int len, t_argb col)
{
	while (len--)
		mmlx_pixel_put(img, x, y + len, col);
}

void			mmlx_prep_img(t_img *img, t_cubd *cubd)
{
	const int	hp = cubd->res.y >> 1;
	int			x;
	int			y;
	char		*p;

	y = -1;
	while (++y < cubd->res.y)
	{
		x = -1;
		while (++x < cubd->res.x)
			mmlx_pixel_put(img, x, y, (y < hp ? cubd->cc : cubd->fc));
	}
}
