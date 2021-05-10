/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:13:30 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/10 21:21:37 by minsunki         ###   ########.fr       */
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
	t_cubd		*cubd;

	cubd = get_meta()->cubd;
	if (line[0] == '\0')
		return (1);
	else if (line[0] == 'R')
		conv_res(line + 1, &cubd->res);
	else if (line[0] == 'S' && line[1] != 'O')
		cubd->sp = conv_tex(line + 1);
	else if (line[0] == 'F')
		cubd->fc = conv_col(line + 1);
	else if (line[0] == 'C')
		cubd->cc = conv_col(line + 1);
	else if (line[0] == 'N' && line[1] == 'O')
		cubd->tex[NORTH] = conv_tex(line + 2);
	else if (line[0] == 'S' && line[1] == 'O')
		cubd->tex[SOUTH] = conv_tex(line + 2);
	else if (line[0] == 'E' && line[1] == 'A')
		cubd->tex[EAST] = conv_tex(line + 2);
	else if (line[0] == 'W' && line[1] == 'E')
		cubd->tex[WEST] = conv_tex(line + 2);
	else
		return (0);
	return (1);
}

void			cub_parse(const char *cub_file)
{
	int			fd;
	char		*line;
	t_list		*list;
	int			rmap;

	rmap = 0;
	list = 0;
	if ((fd = open(cub_file, O_RDONLY)) < 0)
		perror_exit("Failed to read .cub file");
	while (get_next_line(fd, &line))
	{
		if (rmap || !parse(line))
		{
			rmap = 1;
			ft_lstadd_back(&list, ft_lstnew((void *)ft_strdup(line)));
		}
		free(line);
	}
	if (line[0])
		ft_lstadd_back(&list, ft_lstnew((void *)ft_strdup(line)));
	free(line);
	map_parse(list);
	ft_lstclear(&list, free);
}
