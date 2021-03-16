/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_moving.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:15:16 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/16 14:37:06 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void    ft_go_f_b(t_all *all)
{
    if (all->data.forward == 1)
    {
        if (all->map.cub[all->ray.posx + (all->ray.dirx * all->
                ray.movespeed * 2)][all->ray.posy] == '0')
            all->ray.posx += all->ray.dirx * all->ray.movespeed;
        

    }
}