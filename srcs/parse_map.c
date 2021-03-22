/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:57 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/22 11:05:34 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_murs(t_all *all)
{
	int i;

	i = 0;
	while (i < all->nblines)
	{
		if (all->map[i][0] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < all->nblines)
	{
		if (all->map[i][all->sizeline - 1] != '1')
			return (1);
		i++;
	}
	if (ft_murs_util(all->map[0]) == 1)
		return (1);
	if (ft_murs_util(all->map[all->nblines - 1]) == 1)
		return (1);
	return (0);
}

int		ft_copy_map(char *str, t_all *all)
{
	static int	i = 0;
	int			j;

	j = 0;
	all->map[i] = NULL;
	if (!(all->map[i] = malloc(sizeof(char) * all->sizeline + 1)))
		return (0);
	while (str[j] != '\0')
	{
		if (ft_start_pos(str[j], all, i, j) == 1)
			all->map[i][j] = '0';
		else if (str[j] == ' ')
			all->map[i][j] = '1';
		else
			all->map[i][j] = str[j];
		j++;
	}
	while (j <= (all->sizeline - 1))
	{
		all->map[i][j] = '1';
		j++;
	}
	all->map[i][j] = '\0';
	i++;
	return (0);
}

int		ft_is_map(char *str, t_all *all)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (ft_charinstr(str, '1') == 1 || ft_charinstr(str, '0') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
					&& str[i] != '\t')
			{
				if (all->insidemap == 1)
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
	static int	snblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_is_map(str, all) == 1)
	{
		if (all->f == -1 || all->c == -1 || all->no == NULL ||
				all->so == NULL || all->we == NULL ||
				all->ea == NULL || all->sp == NULL)
			all->err = 2;
		if ((i = ft_strlen(str)) > ssizeline)
			ssizeline = i;
		snblines = snblines + 1;
	}
	all->nblines = snblines;
	all->sizeline = ssizeline;
}
