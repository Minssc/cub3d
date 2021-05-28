/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:13:30 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/28 15:56:33 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_byte	conv_res(char *line, t_meta *meta, t_cubd *cubd, t_res *res)
{
	char		*spp;
	t_res		sres;

	cp_check_lflag(&cubd->lflag, CP_R);
	while (*line == ' ')
		line++;
	if (!cp_res_isvalid(line))
		perror_exit("Invalid resoultion data (only [ 0123456789] allowed");
	if (!(spp = ft_strchr(line, ' ')))
		perror_exit("Invalid resolution (not enough elements)");
	if ((res->x = ft_atoi(line)) <= 0)
		perror_exit("Invalid resolution (x <= 0)");
	if ((res->y = ft_atoi(spp + 1)) <= 0)
		perror_exit("Invalid resolution (y <= 0)");
	if ((spp = ft_strchr(spp + 1, ' ')) && cp_valid_islice(spp + 1))
		perror_exit("Invalid resolution (too many elements)");
	mlx_get_screen_size(meta->mlx, &sres.x, &sres.y);
	res->x = ft_maxi(ft_mini(res->x, sres.x), 400);
	res->y = ft_maxi(ft_mini(res->y, sres.y), 300);
	return (CP_R);
}

static t_argb	conv_col(char *line, t_cubd *cubd, t_byte key)
{
	t_argb		argb;
	int			val;
	char		*com;

	cp_check_lflag(&cubd->lflag, key);
	argb = 0;
	while (*line == ' ')
		line++;
	cp_col_validate(line);
	if ((val = ft_atoi(line)) < 0 || val > 255)
		perror_exit("Invalid color (R value out of range)");
	argb = val << 8;
	com = ft_strchr(line, ',');
	if ((val = ft_atoi(com + 1)) < 0 || val > 255)
		perror_exit("Invalid color (G value out of range)");
	argb = (argb + val) << 8;
	com = ft_strchr(com + 1, ',');
	if ((val = ft_atoi(com + 1)) < 0 || val > 255)
		perror_exit("Invalid color (B value out of range)");
	argb += val;
	return (argb);
}

static void		conv_tex(char *line, t_meta *m, t_tex *t, t_byte key)
{
	t_img		im;
	t_pnt2		p;

	cp_check_lflag(&m->cubd->lflag, key);
	while (*line == ' ')
		line++;
	if (!(im.obj = mlx_xpm_file_to_image(m->mlx, line, &t->x, &t->y)))
		perror_exit("failed to load texture");
	if (!(im.addr = mlx_get_data_addr(im.obj, &im.bpp, &im.llen, &im.endi)))
		perror_exit("mlx_get_data_addr failed @conv_tex");
	im.bypp = im.bpp >> 3;
	if (!(t->dat = (t_argb **)ft_calloc(t->y, sizeof(t_argb *))))
		perror_exit("calloc failed @conv_tex for t->dat");
	p.y = -1;
	while (++p.y < t->y)
		if (!(t->dat[p.y] = (t_argb *)ft_calloc(t->x, sizeof(t_argb))))
			perror_exit("calloc failed @conv_tex for t->dat[y]");
	while (--p.y >= 0)
	{
		p.x = -1;
		while (++p.x < t->x)
			t->dat[p.y][p.x] = mmlx_pixel_at(&im, p.x, p.y);
	}
	mlx_destroy_image(m->mlx, im.obj);
}

static int		parse(t_meta *meta, t_cubd *cubd, char *line)
{
	if (line[0] == '\0')
		return (1);
	else if (line[0] == 'R')
		conv_res(line + 1, meta, cubd, &cubd->res);
	else if (line[0] == 'S' && line[1] != 'O')
		conv_tex(line + 1, meta, &cubd->sp, CP_S);
	else if (line[0] == 'F')
		cubd->fc = conv_col(line + 1, cubd, CP_F);
	else if (line[0] == 'C')
		cubd->cc = conv_col(line + 1, cubd, CP_C);
	else if (line[0] == 'N' && line[1] == 'O')
		conv_tex(line + 2, meta, &cubd->tex[NORTH], CP_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		conv_tex(line + 2, meta, &cubd->tex[SOUTH], CP_SO);
	else if (line[0] == 'E' && line[1] == 'A')
		conv_tex(line + 2, meta, &cubd->tex[EAST], CP_EA);
	else if (line[0] == 'W' && line[1] == 'E')
		conv_tex(line + 2, meta, &cubd->tex[WEST], CP_WE);
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
			if (!rmap++)
				cp_check_lflag(&meta->cubd->lflag, 0);
			ft_lstadd_back(&list, ft_lstnew((void *)ft_strdup(line)));
		}
		free(line);
	}
	if (line[0])
		ft_lstadd_back(&list, ft_lstnew((void *)ft_strdup(line)));
	free(line);
	line = map_parse(list);
	ft_lstclear(&list, free);
	if (line)
		perror_exit(line);
}
