/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:38:56 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/07 10:02:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <mlx.h>
# include <math.h>
# include <sys/stat.h>

# define RED "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define BUFFER_SIZE	4096
# define KEY_ESCAPE 65307
# define KEY_ROTATE_LEFT 65361
# define KEY_ROTATE_RIGHT 65363
# define KEY_FORWARD 119
# define KEY_BACK 115
# define KEY_RIGHT 100
# define KEY_LEFT 97

typedef struct		s_spr_coo
{
	double			x;
	double			y;
}					t_spr_coo;

typedef struct		s_sprite
{
	int				nbspr;
	int				*order;
	double			*dist;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstartx;
	int				drawstarty;
	int				drawendy;
	int				drawendx;
	int				spritewidth;
	double			*zbuffer;
}					t_sprite;

typedef struct		s_texture
{
	int				texdir;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}					t_texture;

typedef struct		s_ray
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			camerax;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			movespeed;
	double			rotspeed;
	int				x;
	int				texture;
}					t_ray;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				minimapechelle;
	int				width;
	int				height;
	void			*img2;
	int				*addr2;
}					t_data;

typedef struct		s_all
{
	int				resx;
	int				resy;
	int				i;
	int				f;
	int				c;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
	int				nblines;
	int				sizeline;
	char			**map;
	char			start_pos;
	int				spawnx;
	int				spawny;
	int				indicateur;
	int				indicateur2;
	int				errored;
	int				save;
	int				screenx;
	int				screeny;
	int				err;
	int				spawn_nb;
	int				emptyline;
	int				is_in_map;
	int				count;
	int				count2;
	int				sum;
	int				wrongcharmap;
	t_data			texture[5];
	t_data			data;
	t_ray			ray;
	t_texture		tex;
	t_sprite		s;
	t_spr_coo		*sxy;
}					t_all;

int					ft_start(char *str, t_all *all);
void				ft_parse(char *filename, t_all *all);
int					ft_map_parsing(char *filename, t_all *all);
int					ft_str_has(char *str, char c);
int					ft_spawn_and_spr(char c, t_all *all, int i, int j);
void				ft_color_resolution(char **str, t_all *all);
void				ft_init(t_all *all);
int					ft_line_is_map(char *str, t_all *all);
void				ft_map(char *str, t_all *all);
int					ft_map_copy(char *str, t_all *all);
void				ft_init_sprite(t_all *all);
int					ft_raycast(t_all *all);
int					ft_ray(t_all *all);
int					ft_press_key(int key, t_all *all);
int					ft_release_key(int key, t_all *all);
int					ft_column_color(t_all *all);
void				ft_ray_init(t_all *all);
void				ft_ray_init_2(t_all *all);
void				ft_init_texture(t_all *all);
void				ft_init_sprite2(t_all *all, int i, int j, int v);
void				ft_stepsidedist(t_all *all);
void				ft_incrementray(t_all *all);
void				ft_drawstartend(t_all *all);
void				ft_swap(t_all *all);
void				ft_forward_back(t_all *all);
void				ft_left_right(t_all *all);
void				ft_rotate_right_left(t_all *all);
void				ft_error(t_all *all, int i, char *str);
int					ft_free_mlx(t_all *all);
void				ft_verify_errors(t_all *all);
void				ft_header(t_all *all, int fd);
void				ft_save(t_all *all);
void				ft_sprite(t_all *all);
void				ft_init2(t_all *all);
int					get_next_line(int fd, char **line, t_all *all);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_subbuff(char *buff, int start, int len);
void				ft_init_dir(t_all *all);
void				ft_ray_init_3(t_all *all);
void				ft_rotate_left(t_all *all, double olddirx);
int					ft_empty_line(char *str);
int					ft_check_save(char *str);
int					ft_map_last(t_all *all);
int					ft_skipspace(char *line, int *i);
int					ft_colors(t_all *all, int *color, char *line, int *i);
void				ft_res(t_all *all, char *line, int *i);
int					ft_atoi(char *line, int *i);
int					ft_texture(t_all *all, char **tex, char *line, int *i);
int					ft_name_check(char *str, char *end);
char				*ft_strdup(const char *s1);
void				ft_parsing_error(t_all *all);
int					check_map_content(t_all *all, int i, int j);
int					ft_check_above(t_all *all, int i, int j);
int					ft_check_below(t_all *all, int i, int j);
int					ft_check_left(t_all *all, int i, int j);
int					ft_check_right(t_all *all, int i, int j);
int					ft_check_map(t_all *all);

#endif
