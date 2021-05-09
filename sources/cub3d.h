/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:30:45 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/09 20:57:47 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include "libft/libft.h"
#include <stdio.h>

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef unsigned int	t_argb;
typedef unsigned char	t_byte;

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

void					cub_parse(const char *cub_file);
void					map_parse(t_list *list);

void					map_validate(t_map *map);
t_byte					map_at(t_map *map, int y, int x);
t_byte					map_char_to_dir(t_byte c);

void					perror_exit(char *estr);

int						cubd_init(void);
void					cubd_destroy(void);

#endif
