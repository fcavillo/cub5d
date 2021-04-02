/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:00 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/02 11:35:12 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_texture(t_all *all, char **tex, char *line, int *i)
{
	char	*texture_file;
	int		j;

	if (ft_map_last(all) == -1)
		return (4);
	if (*tex != NULL)
		return (9);
	(*i) += 2;//passer les lettres
	ft_skipspace(line, i);
	j = (*i);
	printf("-%c%c%c-\n", line[*i], line[*i + 1], line[*i + 2]);
	if (line[*i] != '.' || line[(*i) + 1] != '/')
		all->err = 10;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(texture_file = malloc(sizeof(char) * (*i - j + 1))))
		return (0);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		texture_file[j++] = line[(*i)++];
	texture_file[j] = '\0';
	if (ft_name_check(texture_file, "xpm") == 0 || line[*i] != '\0')
		all->err = 10;
	*tex = ft_strdup(texture_file);
	free(texture_file);
	return (0);
}

void	ft_res(t_all *all, char *line, int *i)
{
	all->i = 1; //whi
	if (ft_map_last(all) == -1)
		all->err = 4;
	if (all->resx != 0 || all->resy != 0)
		all->err = 5;
	(*i)++;
	all->resx = ft_atoi(line, i);
	all->resy = ft_atoi(line, i);
	if (all->resx > 2560)
		all->resx = 2560;
	if (all->resy > 1400)
		all->resy = 1400;
	if (all->resx <= 0 || all->resy <= 0 || line[*i] != '\0')
		all->err = 6;
}

int		ft_colors(t_all *all, int *color, char *line, int *i)
{
	int r;
	int g;
	int b;

	if (ft_map_last(all) == -1)
		return (4);
	if (*color != -1)
		return (8);
	(*i)++;
	r = ft_atoi(line, i);
	ft_skipspace(line, i);
	if (line[(*i)++] != ',')
		return (7);
	g = ft_atoi(line, i);
	ft_skipspace(line, i);
	if (line[(*i)++] != ',')
		return (7);
	b = ft_atoi(line, i);
	ft_skipspace(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255
				|| r < 0 || g < 0 || b < 0)
		return (7);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}
