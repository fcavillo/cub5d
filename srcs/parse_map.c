/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:57 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/23 16:25:38 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/*
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
*/
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
//		else if (str[j] == ' ')
//			all->map[i][j] = '1'; remplace par des '1'
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
				if (all->is_in_map == 1) //check 
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
//	static int	static_nblines = 0;
//	static int	static_sizeline = 0;

	i = 0;
	if (ft_line_is_map(str, all) == 1) //si ya un char hors map on exclut 
	{
		if (all->so == NULL || all->no == NULL || all->we == NULL
		|| all->f == -1 || all->c == -1 || all->ea == NULL 
		|| all->sp == NULL)
			all->err = 4;
		if ((i = ft_strlen(str)) > all->sizeline)
			all->sizeline = i;
		all->nblines = all->nblines + 1;
	}
//	all->nblines = static_nblines;
//	all->sizeline = static_sizeline;
}
/*
void	ft_map(char *str, t_all *all)
{
	int			i;
	static int	static_nblines = 0;
	static int	static_sizeline = 0;

	i = 0;
	if (ft_line_is_map(str, all) == 1) //si ya un char hors map on exclut 
	{
		if (all->so == NULL || all->no == NULL || all->we == NULL
		|| all->f == -1 || all->c == -1 || all->ea == NULL 
		|| all->sp == NULL)
			ft_error(all, 1, "Missing param before Map\n");
		if ((i = ft_strlen(str)) > static_sizeline)
			static_sizeline = i;
		static_nblines = static_nblines + 1;
	}
	all->nblines = static_nblines;
	all->sizeline = static_sizeline;
}*/
