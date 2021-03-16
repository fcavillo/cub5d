/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:32:11 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/16 14:14:06 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    ft_draw(t_all *all)
{
    if (all->ray.side == 0)
        all->ray.perpwalldist = ((double)all->ray.mapx - all->ray.posx 
            + (1 - (double)all->ray.stepx) / 2) / all->ray.raydirx;
    else
        all->ray.perpwalldist = ((double)all->ray.mapy - all->ray.posy 
            + (1 - (double)all->ray.stepy) / 2) / all->ray.raydiry;
    all->ray.lineheight = (int)(all->win.y / all->ray.perpwalldist);
	all->ray.drawstart = -all->ray.lineheight / 2 + all->win.y / 2;
	if (all->ray.drawstart < 0)
		all->ray.drawstart = 0;
	all->ray.drawend = all->ray.lineheight / 2 + all->win.y / 2;
	if (all->ray.drawend >= all->win.y || all->ray.drawend < 0)
		all->ray.drawend = all->win.y - 1;
}

void    ft_increment_ray(t_all *all)
{
    while (all->ray.hit == 0)
    {
        if (all->ray.sidedistx < all->ray.sidedisty)
        {
            all->ray.sidedistx += all->ray.deltadistx;
            all->ray.mapx += all->ray.stepx;
            all->ray.side = 0;
        }
        else
        {
            all->ray.sidedisty += all->ray.deltadisty;
            all->ray.mapy += all->ray.stepy;
            all->ray.side = 1;            
        }
        if (all->map.cub[all->ray.mapx][all->ray.mapy] == '1')
            all->ray.hit = 1;
    }
    ft_draw(all);
}

void    ft_step_sidedist(t_all *all)
{
    if (all->ray.raydirx < 0)
    {
        all->ray.stepx = -1;
        all->ray.sidedistx = (all->ray.posx - all->ray.mapx) 
                                * all->ray.deltadistx;
    }
    else
    {
        all->ray.stepx = 1;
        all->ray.sidedistx = (all->ray.mapx + 1 - all->ray.posx) 
                                * all->ray.deltadistx;        
    }
    if (all->ray.raydiry < 0)
    {
        all->ray.stepy = -1;
        all->ray.sidedisty = (all->ray.posy - all->ray.mapy) 
                                * all->ray.deltadisty;
    }
    else
    {
        all->ray.stepy = 1;
        all->ray.sidedisty = (all->ray.mapy + 1 - all->ray.posy) 
                                * all->ray.deltadisty;        
    }
    ft_increment_ray(all);
}

int     ft_raycast(t_all *all)
{
    all->ray.x = 0;
    while (all->ray.x < all->win.x)
    {
        ft_ray_init_2(all);
        ft_step_sidedist(all);
        ft_column_color(all);
        all->spr.zbuffer[all->ray.x] = all->ray.perpwalldist;
        all->ray.x++;
    }
 //   ft_spr(all); A FAIREEEEE
    mlx_put_image_to_window(all->data.mlx_ptr, all->data.mlx_win, all->data.img,
        0, 0);
    ft

    
    return (0);
}