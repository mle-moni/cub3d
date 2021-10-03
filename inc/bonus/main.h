/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:27:50 by mle-moni          #+#    #+#             */
/*   Updated: 2019/11/27 14:51:28 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define TILE_SIZE 32

# define K_ARR_UP 65362
# define K_ARR_DOWN 65364
# define K_ARR_LEFT 65361
# define K_ARR_RIGHT 65363

# define K_A 97
# define K_B 98
# define K_J 32
# define K_F 99

# define TXTR_SIZE 64
# define RT_SPD 0.05
# define MV_SPD 0.005
# define HITBOX 0.7
# define LINE_MAX 8000
# define RAY 1

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		max;
	int		w;
	int		h;
}				t_img;

typedef struct	s_texture
{
	char	*path;
	t_img	img;
}				t_texture;

typedef struct	s_koopa
{
	int			exist;
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
}				t_koopa;

typedef struct	s_castv
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	ray_length;
	double	wall_x;
	int		line_height;
	int		step_x;
	int		step_y;
	int		side;
	int		map_x;
	int		map_y;
	int		txt_id;
	int		texel_x;
	int		hit;
	int		id;
}				t_castv;

typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	int		lives;
	int		bonus;
}				t_player;

typedef struct	s_color
{
	int r;
	int g;
	int b;
}				t_color;

typedef struct	s_keyboard
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		jump;
}				t_keyboard;

typedef struct	s_obj
{
	int		exist;
	t_castv	castv;
	int		x;
	int		w;
	int		h_min;
	int		h_max;
	int		line_height;
}				t_obj;

typedef struct	s_sprite
{
	t_img		frames[32];
	t_img		current_frame;
	int			frame_id;
}				t_sprite;

typedef struct	s_code
{
	int			code[11];
	int			solve;
	int			max;
}				t_code;

typedef struct	s_config
{
	t_player	player;
	void		*init;
	void		*window;
	t_img		img;
	t_keyboard	keyboard;
	int			res_x;
	int			res_y;
	t_texture	text_array[4];
	t_texture	text_s;
	t_color		color_f;
	t_color		color_c;
	char		*error_msg;
	char		**map;
	int			map_w;
	int			map_h;
	int			distance_to_pjt_plane;
	t_color		wt;
	t_color		red;
	t_color		green;
	t_color		black;
	t_obj		obj;
	int			save;
	int			ti;
	int			tj;
	int			ta;
	t_color		tmp_c;
	int			ret;
	long		ms;
	long		dt;
	t_img		main_sp;
	t_img		lose;
	t_img		shell;
	t_img		sky;
	t_img		sky2;
	t_img		heart;
	t_img		win_img;
	int			jump;
	int			shift;
	t_koopa		koopa;
	t_sprite	laiktu;
	int			win;
	t_code		konami;
}				t_config;

void			put_str_fd(const char *str, int fd);
int				is_from_str(char c, char *str);
int				ft_atoi(const char *str, int *i);
int				parsing(t_config *conf, char *path);
char			*ft_str_cat(const char *str, const char *str2);
int				str_len(const char *str);
void			init_config(t_config *conf);
int				init_textures(t_config *conf);
int				free_config(t_config *config);
int				verif_config(t_config *config);
int				put_error(t_config *config);
int				quick_error(char *msg, char *msg2, t_config *config);
int				free_split(char **strs);
double			get_rot(char c);

void			init_color(t_color *color, int r, int g, int b);
int				check_color(t_color color);

void			set_hooks(t_config *conf);
void			move_player(t_config *conf);

void			slice(t_config *conf, int x, int y, int w);
void			reset_img(t_config *conf);
int				get_pixel_index(t_img img, int x, int y);

void			cast_all(t_config *conf);
void			dda(t_config *conf, t_castv *castv, int x);
void			draw_map(t_config *conf);
void			carre(t_config *conf, int x, int y, int w);
void			trait(t_config *conf, int y, int w, t_color color);
void			set_color(t_color *color, int r, int g, int b);
void			fill_space(t_config *conf, int y, int h, t_color color);
void			draw_sprite(t_config *conf);
void			set_sprite_infos(t_config *conf, int x);
void			init_sky_and_floor(t_config *conf);

void			draw_stripe(t_config *conf, t_castv *castv, int x);
void			get_texel_and_tex_id(t_castv *castv);

void			get_microtime(t_config *conf, long *u_time);
void			some_sprites(t_config *conf);
void			display_hud(t_config *conf);
void			jump(t_config *conf);
void			shift_color(t_config *conf, int index, double distance);
void			put_img(t_config *conf, t_img *img, int x, int y);
void			load_sprite(t_config *conf, char *path, t_img *img);
void			frame_update(t_config *conf);
void			save_map(t_config *conf);
int				exit_hook(void *config);

void			koopa_forward(t_config *conf);
void			koopa_attack(t_config *conf);
void			load_laiktu(t_config *conf);

void			collisions(t_config *conf);
t_img			get_texture_by_id(t_config *conf, int id);

void			change_map(t_config *conf);
void			set_code(t_config *conf);
void			konami_step(t_config *conf, int keycode);

#endif
