/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:14:23 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/03 16:12:51 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int     check_map_content(t_all *all, int i, int j)
{
    if (all->map.cub[i][j] == '1' || all->map.cub[i][j] == '2' || all->map.cub[i][j] == '0'
        || all->map.cub[i][j] == 'N' || all->map.cub[i][j] == 'E' || all->map.cub[i][j] == 'W' 
        || all->map.cub[i][j] == 'S' || all->map.cub[i][j] == ' ')
            return (0);
    else
        return (-1);
}

 int    ft_check_above(t_all *all, int i, int j)
 {
     while (i >= 0)
    {
        if (all->map.cub[i][j] == '1')
            return (0);
        i--;
    }
    return (1);
 }

  int    ft_check_below(t_all *all, int i, int j)
 {
     while (i < all->map.y)
    {
        if (all->map.cub[i][j] == '1')
            return (0);
        i++;
    }
    return (1);
 }

  int    ft_check_left(t_all *all, int i, int j)
 {
     while (j >=0)
    {
        if (all->map.cub[i][j] == '1')
            return (0);
        j--;
    }
    return (1);
 }

  int    ft_check_right(t_all *all, int i, int j)
 {
     while (j <= all->map.x)
    {
        if (all->map.cub[i][j] == '1')
            return (0);
        j++;
    }
    return (1);
 }