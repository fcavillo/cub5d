/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:46:44 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/04 10:32:27 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_empty_line(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' &&
				str[i] != '\n' && str[i] != '\r' && str[i] != '\v'
				&& str[i] != '\f')
			return (0);
		i++;
	}
	return (1);
}		
		

int     ft_skipspace(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\r' 
    || line[*i] == '\t' || line[*i] == '\v' || line[*i] == '\f')
    {
        (*i)++;
    }
    return (1);
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

int     ft_name_check(char *str, char *end)
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