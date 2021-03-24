/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/24 11:07:04 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_name_check(char *str, char *end)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if ((i > 4) && str[i - 1] == end[2] && str[i - 2] == end[1]
	&& str[i - 3] == end[0] && str[i - 4] == '.')
		return (1);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int				size_s1;
	char			*copy;
	int				i;

	i = 0;
	size_s1 = ft_strlen((char *)s1);
	if (!(copy = malloc(sizeof(char) * (size_s1 + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int		ft_atoi(char *line, int *i)
{
	int	num;

	num = -1;
	ft_skipspace(line, i);
	if (line[*i] >= '0' && line[*i] <= '9')
		num = 0;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

int		ft_map_last(t_all *all)
{
	if (all->sizeline > 0 && (all->no == NULL || all->so == NULL ||
				all->we == NULL || all->ea == NULL || all->sp == NULL))
		return (-1);
	return (0);
}

int		ft_skipspace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\r'
	|| line[*i] == '\t' || line[*i] == '\v' || line[*i] == '\f')
	{
		(*i)++;
	}
	return (1);
}
