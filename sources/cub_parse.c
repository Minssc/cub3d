/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:53:08 by minsunki          #+#    #+#             */
/*   Upg_cubded: 2021/05/07 15:03:17 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_cubd	*g_cubd;

static void		conv_res(const char *line, t_res *res)
{
	char		*tmp;
	char		*sp;

	while (*line == ' ')
		line++;
	if (!(tmp = ft_strchr(line, ' ')))
		perror_exit("Invalid resolution");
	if (!(sp = ft_substr(line, 0, tmp - line)))
		perror_exit("Invalid resolution");
	if ((res->x = ft_atoi(sp)) <= 0)
		perror_exit("Invalid resolution (x)");
	free(sp);
	if (!(sp = ft_substr(line, tmp - line, -1)))
		perror_exit("Invalid resolution");
	if ((res->y = ft_atoi(sp)) <= 0)
		perror_exit("Invalid resolution (y)");
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
		perror_exit("Invalid color");
	while (spp[i])
		i++;
	if (i != 3)
		perror_exit("Invalid color (incorrect number of elements)");
	while (i--)
	{
		if ((tmp = ft_atoi(spp[2 - i])) < 0 || tmp > 255)
			perror_exit("Invalid color value");
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

static int		parse(const char *line)
{
	if (line[0] == '\0')
		return (1);
	else if (line[0] == 'R')
		conv_res(line + 1, &g_cubd->res);
	else if (line[0] == 'S' && line[1] != 'O')
		g_cubd->sp = conv_tex(line + 1);
	else if (line[0] == 'F')
		g_cubd->fc = conv_col(line + 1);
	else if (line[0] == 'C')
		g_cubd->cc = conv_col(line + 1);
	else if (line[0] == 'N' && line[1] == 'O')
		g_cubd->tex[NORTH] = conv_tex(line + 2);
	else if (line[0] == 'S' && line[1] == 'O')
		g_cubd->tex[SOUTH] = conv_tex(line + 2);
	else if (line[0] == 'E' && line[1] == 'A')
		g_cubd->tex[EAST] = conv_tex(line + 2);
	else if (line[0] == 'W' && line[1] == 'E')
		g_cubd->tex[WEST] = conv_tex(line + 2);
	else
		return (0);
	return (1);
}

static void		print_cubd(t_cubd *g_cubd)
{
	printf(".cub g_cubda start\n");
	printf("R: %dx%d\n",g_cubd->res.x,g_cubd->res.y);
	printf("NO: %s\n",g_cubd->tex[NORTH]);
	printf("SO: %s\n",g_cubd->tex[SOUTH]);
	printf("WE: %s\n",g_cubd->tex[WEST]);
	printf("EA: %s\n",g_cubd->tex[EAST]);
	printf("S: %s\n",g_cubd->sp);
	printf("F: "), pargb(g_cubd->fc);
	printf("C: "), pargb(g_cubd->cc);
	//TODO: print map here
	
	printf(".cub g_cubda end\n");
}

void			cub_parse(const char *cub_file)
{
	int			fd;
	char		*line;
	t_list		*list;
	t_list		*nlist;
	int			rmap;

	rmap = 0;
	list = 0;
	if ((fd = open(cub_file, O_RDONLY)) < 0)
		perror_exit("failed to read .cub file");
	while (get_next_line(fd, &line))
	{
		if (rmap || !parse(line))
		{
			rmap = 1;
			nlist = ft_lstnew((void *)ft_strdup(line));
			ft_lstadd_back(&list, nlist);
		}
	}
	map_parse(list);
	print_cubd(g_cubd);
}
