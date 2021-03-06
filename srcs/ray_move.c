/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:09 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/16 15:37:42 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_rotate_left(t_all *all, double olddirx)
{
	double oldplanex;

	if (all->data.rotate_left == 1)
	{
		olddirx = all->ray.dirx;
		oldplanex = all->ray.planx;
		all->ray.dirx = all->ray.dirx * cos(all->ray.rotspeed / 2) -
			all->ray.diry * sin(all->ray.rotspeed / 2);
		all->ray.diry = olddirx * sin(all->ray.rotspeed / 2) + all->
			ray.diry * cos(all->ray.rotspeed / 2);
		all->ray.planx = all->ray.planx * cos(all->ray.rotspeed / 2) -
			all->ray.plany * sin(all->ray.rotspeed / 2);
		all->ray.plany = oldplanex * sin(all->ray.rotspeed / 2) +
			all->ray.plany * cos(all->ray.rotspeed / 2);
	}
}

/*
** rotating direction and plane vectors
*/

void	ft_rotate_right_left(t_all *all)
{
	double oldplanx;
	double olddirx;

	oldplanx = all->ray.planx;
	olddirx = all->ray.dirx;
	if (all->data.rotate_right == 1)
	{
		all->ray.dirx = all->ray.dirx * cos(-all->ray.rotspeed / 2) -
			all->ray.diry * sin(-all->ray.rotspeed / 2);
		all->ray.diry = olddirx * sin(-all->ray.rotspeed / 2) +
			all->ray.diry * cos(-all->ray.rotspeed / 2);
		all->ray.planx = all->ray.planx * cos(-all->ray.rotspeed / 2)
			- all->ray.plany * sin(-all->ray.rotspeed / 2);
		all->ray.plany = oldplanx * sin(-all->ray.rotspeed / 2) +
			all->ray.plany * cos(-all->ray.rotspeed / 2);
	}
	ft_rotate_left(all, olddirx);
}

void	ft_left_right(t_all *all)
{
	if (all->data.right == 1)
	{
		if (all->map[(int)(all->ray.posx + (all->ray.diry *
					(all->ray.movespeed * 2)))][(int)all->ray.posy] == '0')
			all->ray.posx += all->ray.diry * all->ray.movespeed;
		if (all->map[(int)all->ray.posx][(int)(all->ray.posy -
					all->ray.dirx *
					(all->ray.movespeed * 2))] == '0')
			all->ray.posy -= all->ray.dirx * all->ray.movespeed;
	}
	if (all->data.left == 1)
	{
		if (all->map[(int)(all->ray.posx - all->ray.diry *
					(all->ray.movespeed * 2))][(int)all->ray.posy] == '0')
			all->ray.posx -= all->ray.diry * all->ray.movespeed;
		if (all->map[(int)all->ray.posx][(int)(all->ray.posy +
					all->ray.dirx *
					(all->ray.movespeed * 2))] == '0')
			all->ray.posy += all->ray.dirx * all->ray.movespeed;
	}
	ft_rotate_right_left(all);
}

/*
** if a key is pressed, and the next case is free, move
*/

void	ft_move(t_all *all)
{
	if (all->data.forward == 1)
	{
		if (all->map[(int)(all->ray.posx + (all->ray.dirx * all->
						ray.movespeed * 2))][(int)all->ray.posy] == '0')
			all->ray.posx += all->ray.dirx * all->ray.movespeed;
		if (all->map[(int)(all->ray.posx)][(int)(all->ray.posy +
					(all->ray.diry * all->ray.movespeed * 2))] == '0')
			all->ray.posy += all->ray.diry * all->ray.movespeed;
	}
	if (all->data.back == 1)
	{
		if (all->map[(int)(all->ray.posx - (all->ray.dirx * all->
						ray.movespeed * 2))][(int)(all->ray.posy)] == '0')
			all->ray.posx -= all->ray.dirx * all->ray.movespeed;
		if (all->map[(int)(all->ray.posx)][(int)(all->ray.posy -
					(all->ray.diry * all->ray.movespeed * 2))] == '0')
			all->ray.posy -= all->ray.diry * all->ray.movespeed;
	}
	ft_left_right(all);
}
