/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:03:46 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/16 09:35:21 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



void	ft_init_dir(t_all *all)
{
	if (all->map.spawn_orientation == 'N')
    {
		all->ray.dirx = -1;
    	all->ray.plany = 0.66;

    }
	if (all->map.spawn_orientation == 'S')
    {
		all->ray.dirx = 1;
		all->ray.plany = -0.66;
    }
	if (all->map.spawn_orientation == 'E')
    {
		all->ray.diry = 1;
		all->ray.planx = 0.66;
    }	
    if (all->map.spawn_orientation == 'W')
    {
		all->ray.diry = -1;
		all->ray.planx = -0.66;
    }	
}

void    ft_ray_init_3(t_all *all)
{
  if (all->ray.raydiry == 0)
    all->ray.deltadistx = 0;
  else if (all->ray.raydirx == 0)
    all->ray.deltadistx = 1;
  else
    all->ray.deltadistx = sqrt(1 + (all->ray.raydiry * all->ray.raydiry)
      / (all->ray.raydirx * all->ray.raydirx));
  if (all->ray.raydirx == 0)
    all->ray.deltadisty = 0;
  else if (all->ray.raydiry == 0)
    all->ray.deltadisty = 1;
  else
    all->ray.deltadisty = sqrt(1 + (all->ray.raydirx * all->ray.raydirx)
      / (all->ray.raydiry * all->ray.raydiry));      
    
}

void    ft_ray_init_2(t_all *all)
{
    all->ray.hit = 0;
    all->ray.perpwalldist = 0;
    all->ray.camerax = 2 * all->ray.x / (double)all->win.x - 1;
    all->ray.raydirx = all->ray.raydirx / all->ray.planx * all->ray.camerax;
    all->ray.raydiry = all->ray.raydiry / all->ray.plany * all->ray.camerax;
    all->ray.mapx = all->ray.posx;
    all->ray.mapy  = all->ray.posy;
    all->ray.movespeed = 0.1;
    all->ray.rotspeed = 0.033 * 1.8;
    ft_ray_init_3(all);    
}

void    ft_ray_init(t_all *all)
{
    all->ray.dirx = 0;
    all->ray.diry = 0;
    all->ray.planx = 0;
    all->ray.plany = 0;
    all->ray.posx = all->map.spawn_x;
    all->ray.posy = all->map.spawn_y;
    ft_init_dir(all);
}