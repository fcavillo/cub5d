#include "../includes/cub3d.h"

void	ft_initialisation2(t_all *all)
{
	if (!(all->s.zbuffer = (double *)malloc(sizeof(double) * all->rx)))
		exit(0);
	all->data.forward = 0;
	all->data.back = 0;
	all->data.left = 0;
	all->data.right = 0;
	all->data.rotate_right = 0;
	all->data.rotate_left = 0;
	all->ray.posx = (double)all->dx + 0.5;
	all->ray.posy = (double)all->dy + 0.5;
	all->ray.dirx = 0;
	all->ray.diry = 0;
	all->ray.planx = 0;
	all->ray.plany = 0;
	ft_init_dir(all);
}

void	ft_initialisation3(t_all *all)
{
	all->ray.hit = 0;
	all->ray.perpwalldist = 0;
	all->ray.camerax = 2 * all->ray.x / (double)all->rx - 1;
	all->ray.raydirx = all->ray.dirx + all->ray.planx * \
						all->ray.camerax;
	all->ray.raydiry = all->ray.diry + all->ray.plany * \
						all->ray.camerax;
	all->ray.mapx = (int)all->ray.posx;
	all->ray.mapy = (int)all->ray.posy;
	all->ray.movespeed = 0.1;
	all->ray.rotspeed = 0.033 * 1.8;
	ft_init_more3(all);
}

void	ft_init_texture(t_all *all)
{
	if (all->ray.side == 0 && all->ray.raydirx < 0)
		all->tex.texdir = 0;
	if (all->ray.side == 0 && all->ray.raydirx >= 0)
		all->tex.texdir = 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->tex.texdir = 2;
	if (all->ray.side == 1 && all->ray.raydiry >= 0)
		all->tex.texdir = 3;
	if (all->ray.side == 0)
		all->tex.wallx = all->ray.posy + all->ray.perpwalldist \
						* all->ray.raydiry;
	else
		all->tex.wallx = all->ray.posx + all->ray.perpwalldist \
						* all->ray.raydirx;
	all->tex.wallx -= floor((all->tex.wallx));
}

void	ft_init_sprite(t_all *all)
{
	int i;
	int j;

	i = -1;
	all->s.nbspr = 0;
	ft_verify_errors(all);
	while (++i < all->nblines)
	{
		j = -1;
		while (++j < all->sizeline)
		{
			if (all->map[i][j] == '2')
				all->s.nbspr += 1;
		}
	}
	if (!(all->sxy = (t_spr_coo *)malloc(sizeof(t_spr_coo) * all->s.nbspr)))
		ft_error(all, 1, "Failing to malloc the Sprite coordinates*");
	if (!(all->s.order = (int *)malloc(sizeof(int) * all->s.nbspr)))
		ft_error(all, 1, "Failing to malloc Sprite orders");
	if (!(all->s.dist = (double *)malloc(sizeof(double) * all->s.nbspr)))
		ft_error(all, 1, "Failing to malloc Sprite distance*");
	ft_init_sprite2(all, 0, 0, 0);
	ft_mlx(all);
}

void	ft_init_sprite2(t_all *all, int i, int j, int v)
{
	i = i - 1;
	while (++i < all->nblines)
	{
		j = -1;
		while (++j < all->sizeline)
		{
			if (all->map[i][j] == '2')
			{
				all->sxy[v].x = (double)i + 0.5;
				all->sxy[v].y = (double)j + 0.5;
				v++;
			}
		}
	}
}
