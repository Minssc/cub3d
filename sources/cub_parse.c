/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:53:08 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/07 01:38:48 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		conv_res(const char *line, t_res *res)
{
	char		*tmp;
	char		*sp;

	while (*line == ' ')
		line++;
	if (!(tmp = ft_strchr(line, ' ')))
		perr_exit("Invalid resolution");
	if (!(sp = ft_substr(line, 0, tmp - line)))
		perr_exit("Invalid resolution");
	if ((res->x = ft_atoi(sp)) <= 0)
		perr_exit("Invalid resolution (x)");
	free(sp);
	if (!(sp = ft_substr(line, tmp - line, -1)))
		perr_exit("Invalid resolution");
	if ((res->y = ft_atoi(sp)) <= 0)
		perr_exit("Invalid resolution (y)");
	free(sp);
}

static void pargb(t_argb argb){
	printf("%3d %3d %3d %3d\n",
			(argb>>24)&0xFF,
			(argb>>16)&0xFF,
			(argb>>8)&0xFF,
			argb&0xFF);
}

static t_argb	conv_col(const char *line)
{
	char		**spp;
	int			i;
	t_argb		argb;
	int			tmp;

	i = 0;
	argb = 0;
	while (*line == ' ')
		line++;
	if (!(spp = ft_split(line, ',')))
		perr_exit("Invalid color");
	while (spp[i])
		i++;
	if (i != 3)
		perr_exit("Invalid color (incorrect number of elements)");
	while (i--)
	{
		if ((tmp = ft_atoi(spp[2 - i])) < 0 || tmp > 255)
			perr_exit("Invalid color value");
		argb = (argb << 8) | (tmp & 0xFF);
	}
	return (argb);
}

static char		*conv_tex(const char *line)
{
	//TODO lean miniLibX texture system and properly implement
	while (*line == ' ')
		line++;
	return (ft_strdup(line));
}

static int		parse(const char *line, t_cubd *dat)
{
	if (line[0] == '\0')
		return (1);
	else if (line[0] == 'R')
		conv_res(line + 1, &dat->res);
	else if (line[0] == 'S' && line[1] != 'O')
		dat->sp = conv_tex(line + 1);
	else if (line[0] == 'F')
		dat->fc = conv_col(line + 1);
	else if (line[0] == 'C')
		dat->cc = conv_col(line + 1);
	else if (line[0] == 'N' && line[1] == 'O')
		dat->tex[NORTH] = conv_tex(line + 2);
	else if (line[0] == 'S' && line[1] == 'O')
		dat->tex[SOUTH] = conv_tex(line + 2);
	else if (line[0] == 'E' && line[1] == 'A')
		dat->tex[EAST] = conv_tex(line + 2);
	else if (line[0] == 'W' && line[1] == 'E')
		dat->tex[WEST] = conv_tex(line + 2);
	else
		return (0);
	return (1);
}

static void		print_cubd(t_cubd *dat)
{
	printf(".cub data start\n");
	printf("R: %dx%d\n",dat->res.x,dat->res.y);
	printf("NO: %s\n",dat->tex[NORTH]);
	printf("SO: %s\n",dat->tex[SOUTH]);
	printf("WE: %s\n",dat->tex[WEST]);
	printf("EA: %s\n",dat->tex[EAST]);
	printf("S: %s\n",dat->sp);
	printf("F: "), pargb(dat->fc);
	printf("C: "), pargb(dat->cc);
	//TODO: print map here
	
	printf(".cub data end\n");
}

int				cub_parse(const char *cub_file, t_cubd *dat)
{
	int			fd;
	char		*line;
	t_list		*list;
	t_list		*nlist;
	int			rmap;

	rmap = 0;
	if ((fd = open(cub_file, O_RDONLY)) < 0)
		return (1);
	while (get_next_line(fd, &line))
	{
		if (rmap || !parse(line, dat))
		{
			rmap = 1;
			printf("m:%s\n",line);
			nlist = ft_lstnew((void *)ft_strdup(line));
			ft_lstadd_back(&list, nlist);
		}
	}
	if (!(map_parse(list, dat)))
	{
		//TODO:: free list
		perr_exit("Invalid map");
	}
	print_cubd(dat);
	return (0);
}
