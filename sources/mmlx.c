/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 23:54:37 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/25 23:16:34 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void			mmlx_pixel_put(t_img *img, int x, int y, t_argb col)
{
	char		*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp >> 3));
	*(t_argb *)dst = col;
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

t_argb			mmlx_pixel_at(t_img *img, int x, int y)
{
	char		*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp >> 3));
	return (*(t_argb *)dst);
}

void			mmlx_draw_textured_line(t_meta *m, t_rend *r, t_tex *t, int x)
{
	const int	ty = r->l_start + r->l_len;
	const t_res	*res = &m->cubd->res;
	double		step;
	t_pnt2		tex_p;
	int			y;

	if (r->side == 1 || r->side == 3)
		r->td = r->pl_p.y + r->pwd * r->ray.y;
	else
		r->td = r->pl_p.x + r->pwd * r->ray.x;
	r->td -= floor(r->td);
	tex_p.x = (int)(r->td * t->x);
	if ((r->side == 0 || r->side == 2) && r->ray.y > 0)
		tex_p.x = t->x - tex_p.x - 1;
	if ((r->side == 1 || r->side == 3) && r->ray.x < 0)
		tex_p.x = t->x - tex_p.x - 1;
	step = t->y / (double)r->l_height;
	r->td = (r->l_start - res->y / 2 + r->l_height / 2) * step;
	y = r->l_start - 1;
	while (++y < ty)
	{
		tex_p.y = (int)r->td;
		r->td += step;
		mmlx_pixel_put(m->img, x, y, mmlx_pixel_at(&t->img, tex_p.x, tex_p.y));
	}
}
