/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:30:45 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/29 13:49:11 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# define PI 3.141592653589793
# define RADIAN 0.0174532925199433
# define NORTH 0
# define SOUTH 2
# define EAST 1
# define WEST 3

# define KC_W 119
# define KC_A 97
# define KC_S 115
# define KC_D 100
# define KC_LA 65361
# define KC_UA 65362
# define KC_RA 65363
# define KC_DA 65364
# define KC_ESC 65307
# define KC_CTRL 65513
# define KC_SHIFT 65505
# define KC_SPACE 32

# define CP_F 1
# define CP_C 2
# define CP_NO 4
# define CP_SO 8
# define CP_EA 16
# define CP_WE 32

typedef unsigned int	t_argb;
typedef unsigned char	t_byte;

typedef struct			s_img
{
	void				*obj;
	char				*addr;
	int					bpp;
	int					bypp;
	int					llen;
	int					endi;
}						t_img;

typedef struct			s_pnt2
{
	int					x;
	int					y;
}						t_pnt2;

typedef t_pnt2			t_res;

typedef struct			s_vec2
{
	double				x;
	double				y;
}						t_vec2;

typedef struct			s_trd
{
	t_vec2				delta_v;
	t_pnt2				int_p;
	int					hit;
}						t_trd;

typedef struct			s_map
{
	t_byte				**dat;
	int					x;
	int					y;
	int					sp;
	t_byte				sd;
}						t_map;

typedef struct			s_tex
{
	t_argb				**dat;
	int					x;
	int					y;
}						t_tex;

typedef struct			s_cubd
{
	t_res				res;
	t_tex				tex[4];
	t_argb				fc;
	t_argb				cc;
	t_map				map;
	t_byte				lflag;
	char				*line;
}						t_cubd;

typedef struct			s_rend
{
	t_vec2				pl_p;
	t_vec2				pl_v;
	t_vec2				pane_v;
	t_vec2				ray;
	t_pnt2				map_p;
	t_vec2				delta;
	t_pnt2				step;
	t_vec2				side_v;
	int					side;
	double				pwd;
	int					l_height;
	int					l_len;
	int					l_start;
	int					l_end;
	double				td;
}						t_rend;

typedef struct			s_kb
{
	t_byte				w;
	t_byte				a;
	t_byte				s;
	t_byte				d;
	t_byte				la;
	t_byte				ra;
}						t_kb;

typedef struct			s_meta
{
	void				*mlx;
	void				*win;
	t_img				*img;
	t_cubd				*cubd;
	t_kb				*keys;
	t_rend				rend;
}						t_meta;

t_meta					*get_meta(void);
t_meta					*meta_init(void);
void					meta_destroy(void);

void					cub_parse(t_meta *meta, t_cubd *cubd,
														const char *cub_file);
int						cp_valid_islice(char *str);
void					cp_col_validate(char *line);
void					cp_check_lflag(t_byte *lf, t_byte key);

char					*map_parse(t_list *list);

void					map_validate(t_map *map);
t_byte					map_at(t_map *map, int y, int x);
t_byte					map_char_to_dir(t_byte c);

void					cubd_destroy(t_cubd **cubd);

void					mmlx_window_init(t_meta *meta);
void					mmlx_prep_framebuffer(t_meta *meta);
void					mmlx_prep_img(t_img *img, t_cubd *cubd);
void					mmlx_draw_textured_line(t_meta *m, t_rend *r, t_tex *t,
																		int x);

int						render(t_meta *meta);

int						hook_destroy(void);
int						hook_keypress(int kc, t_meta *meta);
int						hook_keyrelease(int kc, t_meta *meta);
int						hook_think(t_meta *meta);

void					pl_rotate(t_rend *r, double deg);
void					pl_init(t_rend *r, t_map *m);
void					pl_think(t_meta *meta);

void					mexit(int ec);
void					perror_exit(char *estr);

#endif
