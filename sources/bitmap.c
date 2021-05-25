/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 23:16:49 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/26 04:41:39 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_word(t_byte *p, int val)
{
	p[0] = (t_byte)(val & 0x00FF);
	p[1] = (t_byte)(val >> 8 & 0x00FF);
}

static void		set_dword(t_byte *p, int val)
{
	set_word(p, val);
	set_word(p + 2, val >> 16);
}

static void		bmp_data(t_img *img, t_res *res, int fd)
{
	int			x;
	int			y;
	t_argb		p;

	y = -1;
	while (++y < res->y)
	{
		x = -1;
		while (++x < res->x)
		{
			p = mmlx_pixel_at(img, x, res->y - 1 - y);
			write(fd, &p, 4);
		}
	}
}

static void		bmp_header(t_img *img, t_res *res, int fd)
{
	const int	hs = 54;
	t_byte		bh[hs];

	ft_bzero(bh, sizeof(bh));
	set_word(bh, 0x4d42);
	set_dword(bh + 2, 54 + res->x * res->y);
	set_dword(bh + 10, 54);
	set_dword(bh + 14, 40);
	set_dword(bh + 18, res->x);
	set_dword(bh + 22, res->y);
	set_word(bh + 26, 1);
	set_word(bh + 28, img->bpp);
	if (write(fd, bh, hs) < hs)
		perror_exit("write failed @bmp_header");
}

void			img_to_bmp(t_meta *m)
{
	int			fd;

	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		perror_exit("failed to open screenshot.bmp for writing");
	bmp_header(m->img, &m->cubd->res, fd);
	bmp_data(m->img, &m->cubd->res, fd);
}
