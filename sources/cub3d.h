/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:30:45 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/10 22:02:04 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
#include <stdio.h>

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef unsigned int	t_argb;
typedef unsigned char	t_byte;

typedef struct			s_img
{
	void				*obj;
	char				*addr;
	int					bpp;
	int					llen;
	int					endi;
}						t_img;

typedef struct			s_res
{
	int					x;
	int					y;
}						t_res;

typedef struct			s_map
{
	t_byte				**dat;
	int					x;
	int					y;
	int					sp;
	t_byte				sd;
}						t_map;

typedef struct			s_cubd
{
	t_res				res;
	char				*tex[4];
	char				*sp;
	t_argb				fc;
	t_argb				cc;
	t_map				map;
}						t_cubd;

typedef struct			s_meta
{
	void				*mlx;
	void				*win;
	t_img				*img;
	t_cubd				*cubd;
}						t_meta;

t_meta					*get_meta(void);
t_meta					*meta_init(void);
void					meta_destroy(void);

void					cub_parse(const char *cub_file);
void					map_parse(t_list *list);

void					map_validate(t_map *map);
t_byte					map_at(t_map *map, int y, int x);
t_byte					map_char_to_dir(t_byte c);

void					perror_exit(char *estr);

void					cubd_destroy(t_cubd **cubd);

void					mmlx_init(t_meta *meta);
void					mmlx_pixel_put(t_img *img, int x, int y, t_argb col);
void					mmlx_draw_vline(t_img *img, int x, int y, int len,
																t_argb col);
void					mmlx_prep_img(t_img *img, t_cubd *cubd);
int						render(void *p);

#endif
