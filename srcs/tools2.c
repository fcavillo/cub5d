/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 10:47:37 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/24 11:07:18 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_spawn_and_spr(char c, t_all *all, int i, int j)
{
	if (c == '2')
		all->s.nbspr++;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		all->spawn_nb++;
		all->start_pos = c;
		all->spawnx = i;
		all->spawny = j;
		return (1);
	}
	return (0);
}

int		ft_empty_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' &&
				str[i] != '\n' && str[i] != '\r' && str[i] != '\v'
				&& str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

int		ft_str_has(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
