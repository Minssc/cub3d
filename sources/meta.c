/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:34:16 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/27 16:16:05 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_meta				*get_meta(void)
{
	static t_meta	*meta;

	if (!meta && (!(meta = (t_meta *)ft_calloc(1, sizeof(t_meta)))))
		perror_exit("Calloc failed @get_meta for meta");
	return (meta);
}

t_meta				*meta_init(void)
{
	t_meta			*meta;
	t_res			*res;
	t_img			*img;

	meta = get_meta();
	if (!(meta->cubd = (t_cubd *)ft_calloc(1, sizeof(t_cubd))))
		perror_exit("Calloc failed @meta_init on meta->cubd");
	if (!(meta->img = (t_img *)ft_calloc(1, sizeof(t_img))))
		perror_exit("Calloc failed @meta_init on meta->img");
	if (!(meta->keys = (t_kb *)ft_calloc(1, sizeof(t_kb))))
		perror_exit("Calloc failed @meta_init on meta->kb");
	if (!(meta->mlx = mlx_init()))
		perror_exit("mlx_init failed @meta_init");
	return (meta);
}

static void			free_mapd(t_map *map)
{
	int				i;

	i = -1;
	if (map->dat)
	{
		while (++i < map->y)
		{
			if (!map->dat[i])
				break ;
			free(map->dat[i]);
			map->dat[i] = 0;
		}
		free(map->dat);
		map->dat = 0;
	}
}

static void			free_texd(t_tex *t)
{
	int				i;

	if (!t->dat)
		return ;
	i = -1;
	while (++i < t->y)
	{
		if (!t->dat[i])
			break ;
		free(t->dat[i]);
		t->dat[i] = 0;
	}
	free(t->dat);
	t->dat = 0;
}

void				meta_destroy(void)
{
	t_meta			*meta;
	int				i;

	i = -1;
	meta = get_meta();
	free_mapd(&meta->cubd->map);
	while (++i < 4)
		free_texd(&meta->cubd->tex[i]);
	free_texd(&meta->cubd->sp);
	free(meta->cubd);
	free(meta->keys);
	if (meta->img->obj)
		mlx_destroy_image(meta->mlx, meta->img->obj);
	if (meta->mlx && meta->win)
		mlx_destroy_window(meta->mlx, meta->win);
}
