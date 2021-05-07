/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:01:02 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/07 16:40:55 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_cubd	*g_cubd;

static int		valid_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
/*
	line needs at least 2 '1'
	line cannot be empty
*/
static int		validate_line(char *line)
{
	int		onec;
	int		len;
	int		i;

	onec = 0;
	len = 0;
	i = 0;
	while (line[i])
	{
		if (!valid_char(line[i]))
			return (0);
		if (line[i] == '1')
		{
			len = i;
			onec++;
		}
		i++;
	}
	return (onec >= 2 ? len + 1: 0);
}

static void print_map(t_map *map)
{
	printf("MAP DATA---\n");
	for(int i=0; i<map->y; ++i)
	{
		for(int j=0; j<map->x; ++j)
		{
			printf("%c",map->dat[i][j]);
		}
		printf("\n");
	}
	printf("MAP DATA END\n");
}

static void		parse_list(t_list *list)
{
	t_list		*clist;
	t_map		*map;
	int			i;
	int			j;
	char		*line;

	clist = list;
	map = &g_cubd->map;
	j = 0;
	while (clist)
	{
		i = -1;
		line = (char *)clist->content;
		while (line[++i])
			map->dat[j][i] = line[i];
		while (i < map->x)
			map->dat[j][i++] = ' ';
		clist = clist->next;
		j++;
	}
	print_map(map);
}

void			map_parse(t_list *list)
{
	t_map		*map;
	t_list		*clist;
	int			i;
	int			len;

	clist = list;
	map = &g_cubd->map;
	i = -1;
	while (clist)
	{
		if ((len = validate_line((char *)clist->content)) == -1)
			perror_exit("Invalid map data");
		map->x = ft_maxi(map->x, len);
		map->y++;
		clist = clist->next;
	}
	if (!(map->dat = (t_byte **)calloc(map->y, sizeof(t_byte *))))
		perror_exit("Malloc failed on g_cubd->map.dat");
	while (++i < map->y)
		if (!(map->dat[i] = (t_byte *)malloc(sizeof(t_byte) * map->x)))
			perror_exit("Malloc failed on g_cubd->map.dat[x]");
	parse_list(list);
}
