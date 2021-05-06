/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:30:45 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/06 20:00:01 by minsunki         ###   ########.fr       */
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

typedef unsigned int t_argb;

typedef struct	s_res
{
	int			x;
	int			y;
}				t_res;

typedef struct	s_cubd
{
	t_res		res;
	char		*tex[4];
	char		*sp;
	t_argb		fc;
	t_argb		cc;
	char		**map;
}				t_cubd;

int			cub_parse(const char *cub_file, t_cubd *dat);
int			map_parse(t_list *list, t_cubd *dat);
void		perr_exit(char *estr);

#endif
