/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 23:49:49 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/19 00:01:39 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_step(t_rend *r)
{
	if (r->ray.x < 0)
	{
		r->step.x = -1;
		r->side_v.x = (r->pl_p.x - r->map_p.x) * r->delta.x;
	}
	else
	{
		r->step.x = 1;
		r->side_v.x = (r->map_p.x + 1.0 - r->pl_p.x) * r->delta.x;
	}
	if (r->ray.y < 0)
	{
		r->step.y = -1;
		r->side_v.y = (r->pl_p.y - r->map_p.y) * r->delta.y;
	}
	else
	{
		r->step.y = 1;
		r->side_v.y = (r->map_p.y + 1.0 - r->pl_p.y) * r->delta.y;
	}
}

static void		perp_and_height(t_rend *r, t_res *res)
{
	if (!r->side)
		r->pwd = (r->map_p.x - r->pl_p.x + (1 - r->step.x) / 2) / r->ray.x;
	else
		r->pwd = (r->map_p.y - r->pl_p.y + (1 - r->step.y) / 2) / r->ray.y;
	r->l_len = (int)(res->y / r->pwd);
	r->l_start = -r->l_len / 2 + res->y / 2;
	r->l_end = r->l_len / 2 + res->y / 2;
	if (r->l_start < 0)
		r->l_start = 0;
	if (r->l_end >= res->y)
		r->l_end = res->y - 1;
}

int				render(void *p)
{
	static int	i;
	t_meta		*meta;
	t_res		*res;
	t_rend		*rend;

	//if (i)
	//	return (0);
	meta = (t_meta *)p;
	res = &meta->cubd->res;
	rend = &meta->rend;
	i = (i + 1)%res->x;
	ft_bzero(meta->img->addr, res->x * res->y * (meta->img->bpp >> 3));
	mmlx_prep_img(meta->img, meta->cubd);

	//mmlx_draw_vline(meta->img, 250, 50, 100, 0x00FF0000);
	//mmlx_draw_line(meta->img, PNT2(100,0), PNT2(500,500), 0x00FFFFFF);
	//mmlx_draw_vline(meta->img, 450, 300, 200, 0x0000FF00);
	//mmlx_draw_line(meta->img, PNT2(300,300), PNT2(450,450), 0x00FFFFFF);
	//mmlx_draw_line(meta->img, PNT2(0,100), PNT2(100,100), 0x00FFFFFF);
	//mmlx_draw_line(meta->img, PNT2(300,300), PNT2(300,400), 0x000000FF);
	//mmlx_draw_line(meta->img, PNT2(300,300), PNT2(330,230), 0x00FF00FF);
	//mmlx_draw_line(meta->img, PNT2(300,0), PNT2(100,100), 0x00FFFFFF);

	//if (1)
	//	return (0);

	//rend->pl_p = VEC2(2.5, 7);
	//rend->pl_v = VEC2(0.0, -1.0);
	//rend->pane_v = VEC2(0.66, 0.0);

	//cam_rotate(rend, (double)i / res->x * 360.0);

	for(int x = 0; x < res->x; ++x)
	{
		rend->scX = (2 * x) / (double)res->x - 1;
		rend->ray = VEC2(rend->pl_v.x + rend->pane_v.x * rend->scX, 
						rend->pl_v.y + rend->pane_v.y * rend->scX);
		rend->map_p = PNT2((int)rend->pl_p.x, (int)rend->pl_p.y);
		rend->delta = VEC2(fabs(1 / rend->ray.x), fabs(1 / rend->ray.y));
		rend->hit = 0;
		set_step(rend);
		ray_dda(rend, &meta->cubd->res, &meta->cubd->map);
		perp_and_height(rend, &meta->cubd->res);
		//printf("x:%d\n",x);
		//printf("%d %d\n",rend->l_start, rend->l_end);
		//printf("%lf %lf\n", rend->delta.x, rend->delta.y);
		//printf("%lf %lf\n", rend->side_v.x, rend->side_v.y);
		//printf("%lf %lf\n", rend->ray.x, rend->ray.y);
		//printf("%d %d\n",rend->map_p.x, rend->map_p.y);
		mmlx_draw_vline(meta->img, x, MIN(rend->l_start, rend->l_end),
						ABS(rend->l_end - rend->l_start),
						rend->side ? 0x00FFFFFF : 0x00EEEEEE);
	}
/*
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


*/


	mlx_put_image_to_window(meta->mlx, meta->win, meta->img->obj, 0, 0);
	return (0);
}
