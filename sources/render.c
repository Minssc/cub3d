/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 23:49:49 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/10 22:35:05 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				render(void *p)
{
	static int	i;
	t_meta		*meta;
	t_res		*res;

	meta = (t_meta *)p;
	res = &meta->cubd->res;
	i = (i + 1)%res->x;
	//ft_bzero(meta->img->addr, res->x * res->y * (meta->img->bpp >> 3));
	mmlx_prep_img(meta->img, meta->cubd);
												
		
/*
	mmlx_draw_vline(meta->img, i, 500, 100, 0xFFFFFFFF);
	mmlx_draw_vline(meta->img, 0, 0, res->y, 0x00FF0000);
	mmlx_draw_vline(meta->img, res->x - 1, 0, res->y, 0x000000FF);
*/

	double posX = 3, posY = 3;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	
	for(int x = 0; x < res->x; ++x)
	{
		double cameraX = 2 * x / (double)res->x - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int mapX = posX;
		int mapY = posY;
		double sideDistX, sideDistY;
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		printf("%lf %lf\n",rayDirX, rayDirY);

		int stepX, stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (meta->cubd->map.dat[mapY][mapX])
				hit = 1;
			//printf("%d %d\n",mapX,mapY);
		}
		//printf("%lf %lf\n",sideDistX, sideDistY);
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		int lineHeight = (int)(res->y / perpWallDist);
		//printf("%lf\n",perpWallDist);
		//printf("%d\n",lineHeight);
		int	drawStart = -lineHeight / 2 + res->y / 2;
		if (drawStart < 0) 
			drawStart = 0;
		int drawEnd = lineHeight / 2 + res->y / 2;
		if (drawEnd >= res->y)
			drawEnd = res->y - 1;
		t_argb col = 0x00FF0000;
		if (side)
			col = 0x0000FF00;
		//printf("%d %d %d %d\n", x, drawStart, drawEnd - drawStart, col);
		//mmlx_draw_vline(meta->img, x, drawStart, drawEnd - drawStart, col);
	}



	mlx_put_image_to_window(meta->mlx, meta->win, meta->img->obj, 0, 0);


	return (0);
}
