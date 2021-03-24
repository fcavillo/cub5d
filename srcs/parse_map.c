/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:57 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/24 12:16:27 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_check_map_zero(t_all *all, int i, int j)
{
	if (all->wrongcharmap == 2)
		ft_error(all, 1, "Invalid character in Map\n");
	if (all->map[i][j] == '0')
	{
		if (ft_check_above(all, i, j) || ft_check_below(all, i, j)
			|| ft_check_left(all, i, j) || ft_check_right(all, i, j))
			ft_error(all, 1, "Map must be closed\n");
	}
	return (0);
}

int		ft_check_map(t_all *all)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < all->nblines)
	{
		while (all->map[i][j])
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

int		ft_map_copy(char *str, t_all *all)
{
	static int	i = 0;
	int			j;

	j = 0;
	all->map[i] = NULL;
	if (!(all->map[i] = malloc(sizeof(char) * all->sizeline + 1)))
		return (0);
	while (str[j])
	{
		if (ft_spawn_and_spr(str[j], all, i, j) == 1)
			all->map[i][j] = '0';
		else
			all->map[i][j] = str[j];
		j++;
	}
	while (j <= (all->sizeline - 1))
	{
		all->map[i][j] = ' '; //cmplete avec des espaces
		j++;
	}
	all->map[i][j] = '\0';
	i++;
	return (0);
}

int		ft_line_is_map(char *str, t_all *all)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (ft_str_has(str, '1') == 1 || ft_str_has(str, '0') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
					&& str[i] != '\t')
			{
				if (all->is_in_map == 1)//check
					all->wrongcharmap = 2;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_map(char *str, t_all *all)
{
	int			i;

	i = 0;
	if (ft_line_is_map(str, all) == 1)//si ya un char hors map on exclut
	{
		if (all->so == NULL || all->no == NULL || all->we == NULL
		|| all->f == -1 || all->c == -1 || all->ea == NULL
		|| all->sp == NULL)
			all->err = 4;
		if ((i = ft_strlen(str)) > all->sizeline)
			all->sizeline = i;
		all->nblines = all->nblines + 1;
	}
}
