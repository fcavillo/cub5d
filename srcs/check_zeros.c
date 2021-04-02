/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zeros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:14:23 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/02 10:11:47 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_map_content(t_all *all, int i, int j)
{
	if (all->map[i][j] == '1' || all->map[i][j] == '2' || all->map[i][j] == '0'
		|| all->map[i][j] == 'N' || all->map[i][j] == 'E'
		|| all->map[i][j] == 'W' || all->map[i][j] == 'S'
		|| all->map[i][j] == ' ')
		return (0);
	else
		return (-1);
}

int		ft_check_above(t_all *all, int i, int j)
{
	while (i >= 0)
	{
		if (all->map[i][j] == ' ')
			return (1);
		if (all->map[i][j] == '1')
			return (0);
		i--;
	}
	return (1);
}

int		ft_check_below(t_all *all, int i, int j)
{
	while (i < all->nblines)
	{
		if (all->map[i][j] == ' ')
			return (1);
		if (all->map[i][j] == '1')
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_left(t_all *all, int i, int j)
{
	while (j >= 0)
	{
		if (all->map[i][j] == ' ')
			return (1);
		if (all->map[i][j] == '1')
			return (0);
		j--;
	}
	return (1);
}

int		ft_check_right(t_all *all, int i, int j)
{
	while (j <= all->sizeline)
	{
		if (all->map[i][j] == ' ')
			return (1);
		if (all->map[i][j] == '1')
			return (0);
		j++;
	}
	return (1);
}
