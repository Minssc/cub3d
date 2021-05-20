/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:34:16 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/20 14:23:32 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_meta				*get_meta(void)
{
	static t_meta	*meta;

	if (!meta && (!(meta = (t_meta *)malloc(sizeof(t_meta)))))
		perror_exit("Malloc failed @get_meta");
	return (meta);
}

t_meta				*meta_init(void)
{
	t_meta			*meta;
	t_res			*res;

	meta = get_meta();
	if (!(meta->cubd = (t_cubd *)ft_calloc(1, sizeof(t_cubd))))
		perror_exit("Calloc failed @meta_init on meta->cubd");
	if (!(meta->img = (t_img *)malloc(sizeof(t_img))))
		perror_exit("Malloc failed @meta_init on meta->img");
	if (!(meta->keys = (t_kb *)ft_calloc(1, sizeof(t_kb))))
		perror_exit("Calloc failed @meta_init on meta->kb");
	return (meta);
}

void				meta_destroy(void)
{
	t_meta			*meta;
	int				i;

	i = -1;
	meta = get_meta();
	if (meta->cubd->map.dat)
	{
		while (++i < meta->cubd->map.y)
		{
			if (!meta->cubd->map.dat[i])
				break ;
			free(meta->cubd->map.dat[i]);
			meta->cubd->map.dat[i] = 0;
		}
		free(meta->cubd->map.dat);
		meta->cubd->map.dat = 0;
	}
	free(meta->cubd);
	free(meta->keys);
	mlx_destroy_image(meta->mlx, meta->img->obj);
	mlx_destroy_window(meta->mlx, meta->win);
}
