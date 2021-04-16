/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:12 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/16 14:54:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** if the wall hit was S or N, side = 1
** perpwalldist (distance between the position plane and the wall point hit) 
** lineheight / perpwalldist to get the illusion
** drawstart is -lineheight/2 for the upper half + resy/2 to add middlescreen
** drawend is the opposite
*/

void	ft_drawstartend(t_all *all)
{
	if (all->ray.side == 0)
		all->ray.perpwalldist = ((double)all->ray.mapx - \
				all->ray.posx + (1 - (double)all->ray.
				stepx) / 2) / all->ray.raydirx;
	else
		all->ray.perpwalldist = ((double)all->ray.mapy - \
				all->ray.posy + (1 - (double)all->ray.
				stepy) / 2) / all->ray.raydiry;
	all->ray.lineheight = (int)(all->resy / all->ray.perpwalldist);
	all->ray.drawstart = -all->ray.lineheight / 2 + all->resy / 2;
	if (all->ray.drawstart < 0)
		all->ray.drawstart = 0;
	all->ray.drawend = all->ray.lineheight / 2 + all->resy / 2;
	if (all->ray.drawend >= all->resy || all->ray.drawend < 0)
		all->ray.drawend = all->resy - 1;
}

/*
** increases the ray :
** adds delta and step to side dist and map on X side until Y is closer, etc
*/

void	ft_increment_ray(t_all *all) //increments position one case at a time,  
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
		if (all->map[all->ray.mapx][all->ray.mapy] == '1')
			all->ray.hit = 1;
	}
	ft_drawstartend(all);
}

/*
** calculates step and sidedist
** Example :
** if the raydir is going straight to the left
** raydirx = -1
** -> stepx is negative
** -> sidedistx (distance to next vertical line) =
**		posx (player exact position)
**		- mapx (player square coordinate)
**		x delatdistX (distance between 2 vertical lines, to set the scale)
*/

void	ft_step_sidedist(t_all *all)
{
	if (all->ray.raydirx >= 0)
	{
		all->ray.stepx = 1;
		all->ray.sidedistx = (all->ray.mapx + 1.0 - all->ray.posx) \
							* all->ray.deltadistx;
	}
	else
	{
		all->ray.stepx = -1;
		all->ray.sidedistx = (all->ray.posx - all->ray.mapx) \
							* all->ray.deltadistx;
	}
	if (all->ray.raydiry >= 0)
	{
		all->ray.stepy = 1;
		all->ray.sidedisty = (all->ray.mapy + 1.0 - all->ray.posy) \
							* all->ray.deltadisty;
	}
	else
	{
		all->ray.stepy = -1;
		all->ray.sidedisty = (all->ray.posy - all->ray.mapy) \
							* all->ray.deltadisty;
	}
	ft_increment_ray(all);
}

