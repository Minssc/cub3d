/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:01:02 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 15:56:58 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		valid_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == '2' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int		valid_line(char *line)
{
	while (*line)
	{
		if (!valid_char(*line))
			return (0);
		line++;
	}
	return (1);
}

static int		line_width(char *line)
{
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			len = i;
		i++;
	}
	return (len + 1);
}

static void		parse_list(t_map *map, t_list *list)
{
	t_list		*clist;
	int			i;
	int			j;
	char		*line;

	clist = list;
	j = -1;
	while (++j < map->y)
	{
		i = -1;
		line = (char *)clist->content;
		while (line[++i])
			map->dat[j][i] = line[i];
		while (i < map->x)
			map->dat[j][i++] = ' ';
		clist = clist->next;
	}
}

char			*map_parse(t_list *list)
{
	t_map		*map;
	t_list		*clist;
	int			i;

	clist = list;
	map = &get_meta()->cubd->map;
	i = 0;
	while (clist)
	{
		i++;
		if (!valid_line(clist->content))
			return ("Invalid map data");
		map->x = ft_maxi(map->x, line_width(clist->content));
		if (ft_strchr(clist->content, '1'))
			map->y = i;
		clist = clist->next;
	}
	if (!(map->dat = (t_byte **)ft_calloc(map->y, sizeof(t_byte *))))
		return ("Malloc failed @map_parse on map->dat");
	i = -1;
	while (++i < map->y)
		if (!(map->dat[i] = (t_byte *)malloc(sizeof(t_byte) * map->x)))
			return ("Malloc failed @map_parse map.dat[x]");
	parse_list(map, list);
	return (0);
}
