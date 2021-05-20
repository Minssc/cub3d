/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:13:30 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/20 19:22:46 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		conv_res(char *line, t_res *res)
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

static t_argb	conv_col(char *line)
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

static void		conv_tex(char *line, t_meta *meta, t_tex *tp)
{
	t_img		*img;

	img = &tp->img;
	while (*line == ' ')
		line++;
	if (img->obj)
		mlx_destroy_image(meta->mlx, img->obj);
	//img->obj = mlx_xpm_file_to_image(meta->mlx, line, &tp->x, &tp->y);
	//img->addr = mlx_get_data_addr(img->obj, &img->bpp, &img->llen, &img->endi);
}

static int		parse(t_meta *meta, t_cubd *cubd, char *line)
{
	if (line[0] == '\0')
		return (1);
	else if (line[0] == 'R')
		conv_res(line + 1, &cubd->res);
	else if (line[0] == 'S' && line[1] != 'O')
		conv_tex(line + 1, meta, &cubd->sp);
	else if (line[0] == 'F')
		cubd->fc = conv_col(line + 1);
	else if (line[0] == 'C')
		cubd->cc = conv_col(line + 1);
	else if (line[0] == 'N' && line[1] == 'O')
		conv_tex(line + 2, meta, &cubd->tex[NORTH]);
	else if (line[0] == 'S' && line[1] == 'O')
		conv_tex(line + 2, meta, &cubd->tex[SOUTH]);
	else if (line[0] == 'E' && line[1] == 'A')
		conv_tex(line + 2, meta, &cubd->tex[EAST]);
	else if (line[0] == 'W' && line[1] == 'E')
		conv_tex(line + 2, meta, &cubd->tex[WEST]);
	else
		return (0);
	return (1);
}

void			cub_parse(t_meta *meta, const char *cub_file)
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
		if (rmap || !parse(meta, meta->cubd, line))
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
