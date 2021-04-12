/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:04 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/12 16:34:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_ray_init(t_all *all)
{
	if (!(all->s.zbuffer = (double *)malloc(sizeof(double) * all->resx)))
		exit(0);
	all->data.forward = 0;
	all->data.back = 0;
	all->data.left = 0;
	all->data.right = 0;
	all->data.rotate_right = 0;
	all->data.rotate_left = 0;
	all->ray.dirx = 0;
	all->ray.diry = 0;
	all->ray.planx = 0;
	all->ray.plany = 0;
	all->ray.posx = (double)all->spawnx + 0.5;
	all->ray.posy = (double)all->spawny + 0.5;
	all->mlx_to_free = 1;
	ft_init_direction(all);
}

void	ft_ray_init_2(t_all *all)
{
	all->ray.hit = 0;
	all->ray.perpwalldist = 0;
	all->ray.camerax = 2 * all->ray.x / (double)all->resx - 1;
	all->ray.raydirx = all->ray.dirx + all->ray.planx * \
						all->ray.camerax;
	all->ray.raydiry = all->ray.diry + all->ray.plany * \
						all->ray.camerax;
	all->ray.mapx = (int)all->ray.posx;
	all->ray.mapy = (int)all->ray.posy;
	all->ray.movespeed = MOVSPEED;
	all->ray.rotspeed = ROTSPEED;
	ft_ray_init_3(all);
}

void	ft_init_texture(t_all *all)
{
	if (all->ray.side == 0 && all->ray.raydirx < 0)
		all->tex.texdirection = 0;
	if (all->ray.side == 0 && all->ray.raydirx >= 0)
		all->tex.texdirection = 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->tex.texdirection = 2;
	if (all->ray.side == 1 && all->ray.raydiry >= 0)
		all->tex.texdirection = 3;
	if (all->ray.side == 0)
		all->tex.wallx = all->ray.posy + all->ray.perpwalldist \
						* all->ray.raydiry;
	else
		all->tex.wallx = all->ray.posx + all->ray.perpwalldist \
						* all->ray.raydirx;
	all->tex.wallx -= floor((all->tex.wallx));
}

void	ft_fill_spr_coo(t_all *all, int i, int j, int v)
{
	i = i - 1;
	while (++i < all->line_nb)
	{
		j = -1;
		while (++j < all->linesize)
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

/*
** replaces ' ' with 1
** mallocs sprites
** fills coos
*/

void	ft_init_spr(t_all *all)
{
	int i;
	int j;

	i = -1;
	ft_check_errors(all);
	while (++i < all->line_nb)
	{
		j = -1;
		while (++j < all->linesize)
		{
			if (all->map[i][j] == ' ')
				all->map[i][j] = '1';
		}
	}
	if (!(all->sxy = (t_spr_coo *)malloc(sizeof(t_spr_coo) * all->s.nbspr)))
		ft_error(all, 1, "Failing to malloc the Sprite coordinates*");
	if (!(all->s.order = (int *)malloc(sizeof(int) * all->s.nbspr)))
		ft_error(all, 1, "Failing to malloc Sprite orders");
	if (!(all->s.dist = (double *)malloc(sizeof(double) * all->s.nbspr)))
		ft_error(all, 1, "Failing to malloc Sprite distance*");
	ft_fill_spr_coo(all, 0, 0, 0);
	ft_ray(all);
}
