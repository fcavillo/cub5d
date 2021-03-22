/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:00 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/22 09:11:01 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_atoi2(const char *str, t_all *all)
{
	int		sum;

	sum = 0;
	if (str[1] != ' ' || ft_charinstr((char *)str, ',') == 1)
		all->erreur = 2;
	while (str[all->i] == ' ' || str[all->i] == '\t'
			|| str[all->i] == ',' || str[all->i] == '\n'
			|| str[all->i] == '\r' || str[all->i] == '\v'
			|| str[all->i] == '\f')
		all->i++;
	if (str[all->i] == '-' || str[all->i] == '+')
		all->erreur = 2;
	while (str[all->i] >= '0' && str[all->i] <= '9')
	{
		if (sum > 21474636)
			break ;
		sum = (sum * 10) + (str[all->i] - 48);
		all->i++;
	}
	while (str[all->i] >= '0' && str[all->i] <= '9')
		all->i++;
	return (sum);
}

int		ft_atoi3(const char *str, t_all *all)
{
	int		verify;

	verify = 0;
	if (str[1] != ' ')
		all->erreur = 2;
	ft_atoi3_check(str, all);
	while (str[all->i] == ' ' || str[all->i] == '\t' || str[all->i]
			== ',' || str[all->i] == '\n' || str[all->i] == '\r'
			|| str[all->i] == '\v' || str[all->i] == '\f')
	{
		all->i++;
		verify = 0;
		if (str[all->i] >= '0' && str[all->i] <= '9')
			all->indicateur2++;
		while (str[all->i] >= '0' && str[all->i] <= '9')
		{
			verify = (verify * 10) + str[all->i] - 48;
			all->sum = (all->sum * 10) + (str[all->i] - 48);
			all->i++;
		}
		if (verify > 255 || verify < 0)
			all->erreur = 2;
	}
	return (all->sum);
}

int		ft_path_texture(char *str, char **texture, t_all *all, int j)
{
	all->count2 = 0;
	if (*texture != NULL)
	{
		all->erreur = 2;
		return (0);
	}
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
			|| ft_strlen2(str) <= 2)
		all->erreur = 2;
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			all->erreur = 2;
		j++;
	}
	if (!(*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)))))
		all->erreur = 2;
	while (str[j] != '\0')
	{
		(*texture)[all->count2] = str[j];
		all->count2++;
		j++;
	}
	(*texture)[all->count2] = '\0';
	return (0);
}

void	ft_texture(char *str, t_all *all)
{
	int			i;
	static int	j = 0;

	i = 0;
	if (str[i] == 'S' && str[i + 1] == 'O')
		ft_path_texture(str, &all->no, all, 2);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		ft_path_texture(str, &all->so, all, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ft_path_texture(str, &all->we, all, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ft_path_texture(str, &all->ea, all, 2);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ft_path_texture(str, &all->sp, all, 1);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
			&& str[0] != 'R' && str[0] != 'F' && str[0] != 'C'
			&& str[0] > 65 && str[0] < 122)
		all->erreur = 2;
	j++;
}

void	ft_color_resolution(char **str, t_all *all)
{
	int			i;

	i = 0;
	all->i = 1;
	if (all->sizeline > 0 && (all->no == NULL || all->so == NULL ||
				all->we == NULL || all->ea == NULL || all->sp == NULL))
		all->erreur = 2;
	if ((all->no != NULL || all->so != NULL || all->we != NULL ||
				all->ea != NULL || all->sp != NULL) && (all->resx == 0
				|| all->resy == 0))
		all->erreur = 2;
	if (*str[i] == 'R')
	{
		if (all->resx != 0 && all->resy != 0)
			all->erreur = 2;
		all->resx = ft_atoi2(*str, all);
		all->resy = ft_atoi2(*str, all);
		if (ft_atoi2(*str, all) > 0 || all->resx == 0 || all->resy == 0)
			all->erreur = 2;
	}
	else if (*str[i] == 'F')
		all->f = ft_atoi3(*str, all);
	else if (*str[i] == 'C')
		all->c = ft_atoi3(*str, all);
}
