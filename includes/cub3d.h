/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:38:56 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/15 17:15:38 by user42           ###   ########.fr       */
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

/*
** for Linux azerty :
** KEY_FORWARD 122
** KEY_LEFT 113
** for MLinux querty :
** KEY_FORWARD 119
** KEY_LEFT 97
*/

# define KEY_ESCAPE 65307
# define KEY_ROTATE_LEFT 65361
# define KEY_ROTATE_RIGHT 65363
# define KEY_FORWARD 122
# define KEY_BACK 115
# define KEY_RIGHT 100
# define KEY_LEFT 113

# define MOVSPEED 0.15
# define ROTSPEED 0.15

typedef struct		s_spr_coo
{
	double			x;
	double			y;
}					t_spr_coo;

/*
** zbuffer stores each stripe distance to the pos
** order & dist set from further to closer
** spriteX and spriteY are reletive positions sprite - player
** invdet, transformX and Y are related to matrix multiplication
*/

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

/*
** texdirection gives the orientation of the texture
** wallX : touched point coordinate, x or y depending on side
** texX et Y : touched point coo on the texture itself
*/

typedef struct		s_texture
{
	int				texdirection;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}					t_texture;

/*
** dirX and dirY are the direction vectors
** raydirX and raydirY are the ray directions
** cameraX is the x point on the screen : right =1, left =-1, center 0
** sidedistX and Y : length of ray from current position to next x or y-side
** deltaDistX and Y : length of ray from one x or y-side to next x or y-side
** stepX and Y : what direction to step in x or y-direction (either +1 or -1)
** sideDistX and sideDistY get incremented with deltaDistX with every jump in their direction
** mapX and mapY get incremented with stepX and stepY respectively
** perpwalldist : distance perpenducilar from wall hit point to camera plane (avoid fisheye)
** lineHeight is the height of the vertical wall line
** drawstart and drawend are lowest and highest pixels to fill
** x is used to parse each column during raycast
*/

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
	void			*img2;
	int				*addr2;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				forward;
	int				back;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
	int				width;
	int				height;
}					t_data;

/*
** screenx and screeny are the results of the mlx_get_screen_size ft
** resx and resy are the final window sizes
*/

typedef struct		s_all
{
	int				resx;
	int				resy;
	int				screenx;
	int				screeny;
	int				i;
	int				f;
	int				c;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
	int				line_nb;
	int				line_nb_temp;
	int				linesize;
	char			**map;
	char			start_pos;
	int				spawnx;
	int				spawny;
//	int				indicateur;
	int				indicateur2;
	int				errored;
	int				save;
	int				err;
	int				spawn_nb;
	int				emptyline;
	int				is_in_map;
	int				count2;
	int				sum;
	int				wrongcharmap;
	int				mlx_to_free;
	t_data			texture[5];
	t_data			data;
	t_ray			ray;
	t_texture		tex;
	t_sprite		s;
	t_spr_coo		*sxy;
}					t_all;

int					ft_map_parsing(char *filename, t_all *all);
int					ft_str_has(char *str, char c);
int					ft_spawn_and_spr(char c, t_all *all, int i, int j);
void				ft_color_resolution(char **str, t_all *all);
void				ft_init(t_all *all);
int					ft_line_is_map(char *str, t_all *all);
void				ft_map(char *str, t_all *all);
int					ft_map_copy(char *str, t_all *all);
void				ft_init_spr(t_all *all);
int					ft_ray(t_all *all);
int					ft_press_key(int key, t_all *all);
int					ft_release_key(int key, t_all *all);
int					ft_column_color(t_all *all);
void				ft_ray_init(t_all *all);
void				ft_ray_init_2(t_all *all);
void				ft_init_texture(t_all *all);
void				ft_step_sidedist(t_all *all);
void				ft_swap(t_all *all);
void				ft_forward_back(t_all *all);
void				ft_left_right(t_all *all);
void				ft_rotate_right_left(t_all *all);
void				ft_error(t_all *all, int i, char *str);
int					ft_free_mlx(t_all *all);
void				ft_check_errors(t_all *all);
void				ft_save(t_all *all);
void				ft_sprite(t_all *all);
void				ft_init2(t_all *all);
int					get_next_line(int fd, char **line, t_all *all);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_subbuff(char *buff, int start, int len);
void				ft_init_direction(t_all *all);
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
