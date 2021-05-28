/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 23:54:37 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 15:57:20 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			mmlx_window_init(t_meta *meta)
{
	const t_res	*res = &meta->cubd->res;

	if (!(meta->win = mlx_new_window(meta->mlx, res->x, res->y, "cub3D")))
		perror_exit("mlx_new_window failed @mmlx_init");
}

void			mmlx_prep_framebuffer(t_meta *meta)
{
	const t_res *res = &meta->cubd->res;

    if (!(meta->img->obj = mlx_new_image(meta->mlx, res->x, res->y)))
        perror_exit("mlx_new_image failed @meta_init");
    if (!(meta->img->addr = mlx_get_data_addr(meta->img->obj, &meta->img->bpp,                                                  &meta->img->llen, &meta->img->endi)))
        perror_exit("mlx_get_data_addr failed @meta_init");	
	meta->img->bypp = meta->img->bpp >> 3;
}

void			mmlx_pixel_put(t_img *img, int x, int y, t_argb col)
{
		*(t_argb *)(img->addr + (y * img->llen + x * img->bypp)) = col;
}

void			mmlx_draw_line(t_img *img, t_pnt2 sp, t_pnt2 ep, t_argb col)
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	int			n;

	n = ft_maxi(ft_absi(ep.x - sp.x), ft_absi(ep.y - sp.y));
	dx = (double)(ep.x - sp.x) / n;
	dy = (double)(ep.y - sp.y) / n;
	x = sp.x;
	y = sp.y;
	while (n--)
	{
		mmlx_pixel_put(img, lround(x), lround(y), col);
		x += dx;
		y += dy;
	}
}

void			mmlx_draw_vline(t_img *img, int x, int y, int len, t_argb col)
{
	while (len--)
		mmlx_pixel_put(img, x, y + len, col);
}

void			mmlx_prep_img(t_img *img, t_cubd *cubd)
{
	const t_res	*res = &cubd->res;
	const int	hp = res->y >> 1;
	int			x;
	int			y;

	y = -1;
	while (++y < hp)
	{
		x = -1;
		while (++x < res->x)
			*(t_argb *)(img->addr + (y * img->llen + x * img->bypp)) =
																	cubd->cc;
	}
	--y;
	while (++y < res->y)
	{
		x = -1;
		while (++x < res->x)
			*(t_argb *)(img->addr + (y * img->llen + x * img->bypp)) =
																	cubd->fc;
	}
}

t_argb			mmlx_pixel_at(t_img *img, int x, int y)
{
	return (*(t_argb *)(img->addr + (y * img->llen + x * img->bypp)));
}

static void		dtl_prep(t_meta *m, t_pnt2 *tp, t_tex *t, double *s)
{
	const t_res	*res = &m->cubd->res;
	t_rend		*r = &m->rend;
	
	if (r->side == 1 || r->side == 3)
		r->td = r->pl_p.y + r->pwd * r->ray.y;
	else
		r->td = r->pl_p.x + r->pwd * r->ray.x;
	tp->x = (int)((r->td - (int)r->td) * t->x);
	if ((r->side == 0 || r->side == 2) && r->ray.y > 0)
		tp->x = t->x - tp->x - 1;
	else if ((r->side == 1 || r->side == 3) && r->ray.x < 0)
		tp->x = t->x - tp->x - 1;
	*s = t->y / (double)r->l_height;
	r->td = (r->l_start - (res->y >> 1) + (r->l_height >> 1)) * (*s);
}

void			mmlx_draw_textured_line(t_meta *m, t_rend *r, t_tex *t, int x)
{
	const t_res	*res = &m->cubd->res;
	const t_img	*img = m->img;
	double		step;
	t_pnt2		tp;
	int			y;

	dtl_prep(m, &tp, t, &step);
	y = r->l_start - 1;
	while (++y < r->l_end)
	{
		tp.y = (int)r->td;
		r->td += step;
		*(t_argb *)(img->addr + (y * img->llen + x * img->bypp)) =
													t->dat[tp.y][tp.x];
	}
	if (y < res->y)
		*(t_argb *)(img->addr + (y * img->llen + x * img->bypp)) =
													t->dat[tp.y][tp.x];
}
