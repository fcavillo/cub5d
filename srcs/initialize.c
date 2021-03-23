/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:49 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/23 17:26:50 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init2(t_all *all)
{
	all->start_pos = 'x';
	all->indicateur2 = 0;
	all->errored = 0;
	all->data.img = NULL;
	all->texture[0].img = NULL;
	all->texture[1].img = NULL;
	all->texture[2].img = NULL;
	all->texture[3].img = NULL;
	all->texture[4].img = NULL;
	all->data.mlx_win = NULL;
	all->map = NULL;
	all->s.order = NULL;
	all->s.dist = NULL;
	all->s.zbuffer = NULL;
	all->sxy = NULL;
}

void	ft_init_dir(t_all *all)
{
	if (all->start_pos == 'N')
		all->ray.plany = 0.66;
	if (all->start_pos == 'S')
		all->ray.plany = -0.66;
	if (all->start_pos == 'E')
		all->ray.planx = 0.66;
	if (all->start_pos == 'W')
		all->ray.planx = -0.66;
	if (all->start_pos == 'N')
		all->ray.dirx = -1;
	if (all->start_pos == 'S')
		all->ray.dirx = 1;
	if (all->start_pos == 'E')
		all->ray.diry = 1;
	if (all->start_pos == 'W')
		all->ray.diry = -1;
}

void	ft_ray_init_3(t_all *all)
{
	if (all->ray.raydiry == 0)
		all->ray.deltadistx = 0;
	else if (all->ray.raydirx == 0)
		all->ray.deltadistx = 1;
	else
		all->ray.deltadistx = sqrt(1 + (all->ray.raydiry
			* all->ray.raydiry) / (all->ray.raydirx *
			all->ray.raydirx));
	if (all->ray.raydirx == 0)
		all->ray.deltadisty = 0;
	else if (all->ray.raydiry == 0)
		all->ray.deltadisty = 1;
	else
		all->ray.deltadisty = sqrt(1 + (all->ray.raydirx *
			all->ray.raydirx) / (all->ray.raydiry *
			all->ray.raydiry));
}

void	ft_atoi3_check(const char *str, t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != ',')
		i++;
	if (str[i] == ',')
		j = 1;
	i++;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		all->err = 2;
	if (ft_nb_virgule(str) != 2)
		all->err = 2;
}

void	ft_init(t_all *all)
{
	all->no = NULL;
	all->so = NULL;
	all->we = NULL;
	all->ea = NULL;
	all->sp = NULL;
	all->f = -1;
	all->c = -1;
	all->resx = 0;
	all->resy = 0;
	all->nblines = 0;
	all->sizeline = 0;
	all->map = NULL;
	all->spawnx = 0;
	all->spawny = 0;
	all->spawn_nb = 0;
	all->emptyline = 0;
	all->is_in_map = 0;
	all->count = 0;
	all->sum = 0;
	all->wrongcharmap = 0;
	ft_init2(all);
}
