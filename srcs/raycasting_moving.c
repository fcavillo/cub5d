/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_moving.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:15:16 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/18 09:41:42 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void    ft_go_f_b(t_all *all)
{
    if (all->data.forward == 1)
    {
        if (all->map.cub[(int)(all->ray.posx + (all->ray.dirx * all->
                ray.movespeed * 2))][(int)all->ray.posy] == '0')
            all->ray.posx += all->ray.dirx * all->ray.movespeed;
		if (all->map.cub[(int)(all->ray.posx)][(int)(all->ray.posy +
					(all->ray.diry * all->ray.movespeed * 2))] == '0')
			all->ray.posy += all->ray.diry * all->ray.movespeed;        
    }
    if (all->data.backward == 1)
    {
        if (all->map.cub[(int)(all->ray.posx - (all->ray.dirx * all->
                ray.movespeed * 2))][(int)all->ray.posy] == '0')
            all->ray.posx -= all->ray.dirx * all->ray.movespeed;
		if (all->map.cub[(int)(all->ray.posx)][(int)(all->ray.posy -
					(all->ray.diry * all->ray.movespeed * 2))] == '0')
			all->ray.posy -= all->ray.diry * all->ray.movespeed;
    }
}

void    ft_go_l_r(t_all *all)
{
    if (all->data.right == 1)
    {
        if (all->map.cub[(int)(all->ray.posx + (all->ray.diry * all->
                ray.movespeed * 2))][(int)all->ray.posy] == '0')
            all->ray.posx += all->ray.diry * all->ray.movespeed;
		if (all->map.cub[(int)(all->ray.posx)][(int)(all->ray.posy -
					(all->ray.dirx * all->ray.movespeed * 2))] == '0')
			all->ray.posy -= all->ray.dirx * all->ray.movespeed;        
    }
    if (all->data.left == 1)
    {
        if (all->map.cub[(int)(all->ray.posx - (all->ray.dirx * all->
                ray.movespeed * 2))][(int)all->ray.posy] == '0')
            all->ray.posx -= all->ray.dirx * all->ray.movespeed;
		if (all->map.cub[(int)(all->ray.posx)][(int)(all->ray.posy +
					(all->ray.diry * all->ray.movespeed * 2))] == '0')
			all->ray.posy += all->ray.diry * all->ray.movespeed;
    }
}

void    ft_rotate_l(t_all *all, double olddirx)
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

void    ft_rotate_l_r(t_all *all)
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
	ft_rotate_l(all, olddirx);    
}

