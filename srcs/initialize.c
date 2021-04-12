/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:49 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/12 12:46:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init2(t_all *all)
{
	all->start_pos = 'x';
//	all->indicateur2 = 0;
	all->errored = 0;
	all->data.img = NULL;
	all->texture[0].img = NULL;
	all->texture[1].img = NULL;
	all->texture[2].img = NULL;
	all->texture[3].img = NULL;
	all->texture[4].img = NULL;
	all->data.mlx_win = NULL;
	all->map = NULL;
	all->s.nbspr = 0;
	all->s.order = NULL;
	all->s.dist = NULL;
	all->s.zbuffer = NULL;
	all->sxy = NULL;
	all->mlx_to_free = 0;
}

/*
** initialises the direction :
** exemple : si on démarre N, le plan est droit vers en haut donc plany = 0.66
*/

void	ft_init_direction(t_all *all) // are x and y fucking inversed
{
	if (all->start_pos == 'E')
	{
		all->ray.planx = 0.66;
		all->ray.diry = 1;
	}
	if (all->start_pos == 'W')
	{
		all->ray.planx = -0.66;
		all->ray.diry = -1;
	}
	if (all->start_pos == 'N')
	{
		all->ray.plany = 0.66;
		all->ray.dirx = -1;
	}
	if (all->start_pos == 'S')
	{
		all->ray.plany = -0.66;
		all->ray.dirx = 1;
	}
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

void	ft_init(t_all *all)
{
	all->save = 0;
	all->no = NULL;
	all->so = NULL;
	all->we = NULL;
	all->ea = NULL;
	all->sp = NULL;
	all->f = -1;
	all->c = -1;
	all->resx = 0;
	all->resy = 0;
	all->line_nb = 0;
	all->linesize = 0;
	all->map = NULL;
	all->spawnx = 0;
	all->spawny = 0;
	all->spawn_nb = 0;
	all->emptyline = 0;
	all->is_in_map = 0;
	all->line_nb_temp = 0;
	all->sum = 0;
	all->wrongcharmap = 0;
	ft_init2(all);
}
