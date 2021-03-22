/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:20:11 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/18 11:06:59 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

#define RED "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define BUFFER_SIZE	4096
#define KEY_ESCAPE 65307
#define KEY_ROTATE_LEFT 65361
#define KEY_ROTATE_RIGHT 65363
#define KEY_FORWARD 119
#define KEY_BACK 115
#define KEY_RIGHT 100
#define KEY_LEFT 97

typedef struct s_ray
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
    int             stepx;
    int             stepy;
    int             x;
    int				hit; //was a wall hit
	int				side; //NS or EW
	double			perpwalldist; //length of ray from one x or y-side to next x or y-side
	double			raydirx;
	double			raydiry;
	double			camerax;
    int				mapx;//current square
	int				mapy;//current square
    double			movespeed;
	double			rotspeed;
	double			deltadistx;
	double			deltadisty;
    double			sidedistx;
	double			sidedisty;
    int				lineheight;
	int				drawstart;
	int				drawend;
}               t_ray;

typedef struct s_data
{
    void       *mlx_ptr;
    void        *mlx_win;
    int         screenx;
    int         screeny;
    void        *img;
    int         width;
    int         height;
    int         *addr;
	int			*addr2;
	void		*img2;
    int         endian;
    int         bits_per_pixel;
    int         line_length;
    int     forward;
    int     backward;
    int     left;
    int     right;
    int     rotate_left;
    int     rotate_right;
    
}               t_data;


typedef struct  s_map
{
    char    **cub;
    int     x;
    int     y;
    int     spr_nb;
    int     spawn_nb;
    int     spawn_x;
    int     spawn_y;
    char    spawn_orientation;
    int     inmap;
    int     charmap;
    int     count;
    int     emptyline;
}           t_map;

typedef struct s_win
{
    int     x;
    int     y;
}           t_win;

typedef struct	s_sprite
{
	int		x;
	int		y;
}			t_sprite;

typedef struct s_spr
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
}           t_spr;


typedef struct s_tex
{
    char    *n;
    char    *s;
    char    *e;
    char    *w;
    char    *spr;
    int    c;
    int    f;
	int				texdir;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
}              t_tex;



typedef struct  s_all
{
    int     save;
    int     err;
    int     err2;
    t_map   map;
    t_win   win;
    t_tex   tex; //=t
	t_sprite	*sprite;
    t_ray       ray;
    t_data      data;
    t_data      texture[5];
    t_spr       spr;
}           t_all; 


void    ft_init(t_all *all);
int		ft_strlen(char *str);
int     ft_check_save(char *str);
void    ft_error(t_all *all, char *str);
int     ft_skipspace(char *line, int *i);
int		ft_atoi(char *line, int *i);
char	*ft_strdup(const char *s);
void     ft_res(t_all *s, char *line, int *i);
int     ft_texture(t_all *all, char **tex, char *line, int *i);
int     ft_colors(t_all *all, int *color, char *line, int *i);
int		get_next_line(int fd, char **line, t_all *all);
int		ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
int     ft_name_check(char *str, char *end);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_subbuff(char *buff, int start, int len);
void    ft_map(char *line, t_all *all);
int		ft_str_has(char *str, char c);
int     ft_map_parsing(char *mapname, t_all *all);
int		ft_empty_line(char *str);
int     ft_spawn_and_sprite(char c, t_all *all, int i, int j);
int     ft_load_sprite(t_all *all);
int    ft_check_above(t_all *all, int i, int j);
int    ft_check_below(t_all *all, int i, int j);
int    ft_check_left(t_all *all, int i, int j);
int    ft_check_right(t_all *all, int i, int j);
int     check_map_content(t_all *all, int i, int j);
void	free_all(t_all *all);
int    ft_check_map(t_all *all);
int     ft_check_map_zero(t_all *all, int i, int j);
void	free_all(t_all *all);
void		ft_check_errors(t_all *all);
void    ft_ray_init(t_all *all);
int     ft_ray(t_all *all);
int		ft_free_mlx(t_all *all);
int     ft_press_key(int key, t_all *all);
int     ft_raycast(t_all *all);
void    ft_ray_init_2(t_all *all);
void    ft_step_sidedist(t_all *all);
void    ft_column_color(t_all *all);
void	ft_init_tex(t_all *all);
void    ft_go_f_b(t_all *all);
void    ft_go_l_r(t_all *all);
void    ft_rotate_l_r(t_all *all);
int     ft_release_key(int key, t_all *all);
void	ft_spr(t_all *all);









void test(t_all *all);


#endif