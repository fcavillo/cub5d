/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:56:22 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/10 11:12:14 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int     ft_spawn_and_sprite(char c, t_all *all, int i, int j)
{
	if (c == '2')
		all->map.spr_nb++;
	if (c == 'W' || c == 'S' || c == 'E' || c == 'N')
	{
		all->map.spawn_orientation = c;
		all->map.spawn_x = i;
		all->map.spawn_y = j;
		all->map.spawn_nb++;
		return (1);           
	}
	return (0);
}

int ft_sprite_coord(t_all *all, int i, int j)
{
	static int a = 0;
	
	if (all->map.cub[i][j] == '2')
	{
		all->sprite[a].x = i;
		all->sprite[a].y = j;
		a++;   
	}
	return(0);
}

int     ft_load_sprite(t_all *all)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (!(all->sprite = malloc(sizeof(t_sprite) * all->map.spr_nb)))
		return (-1);
	while (i < all->map.y)
	{
		while (all->map.cub[i][j])
		{
			ft_sprite_coord(all, i, j);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);  
}

int     ft_check_map_zero(t_all *all, int i, int j)
{
	if (all->map.charmap == 2)
	{
		ft_error(all, "Invalid character in Map\n");
		return (-1);
	}
	if (all->map.cub[i][j] == '0')
	{
	   if (ft_check_above(all, i, j) || ft_check_below(all, i, j) 
			|| ft_check_left(all, i, j) || ft_check_right(all, i, j))
		{
			ft_error(all, "Map must be closed\n");
			return (-1);
		}
	}
	return (0);
}

int     ft_check_map(t_all *all)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < all->map.y)
	{
		while (all->map.cub[i][j])
		{
			if (ft_check_map_zero(all, i, j) == -1)
				return (-1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
