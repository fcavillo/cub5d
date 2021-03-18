/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:55:12 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/18 10:56:59 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_dist_order2(t_all *all) 
{
	int i;

	i = -1;
	while (++i < all->spr.nbspr)
	{
		all->spr.order[i] = i;
		all->spr.dist[i] = ((all->ray.posx - all->sprite[i].x) *
				(all->ray.posx - all->sprite[i].x) + (all->ray.posy -
					all->sprite[i].y) * (all->ray.posy - all->sprite[i].y));
	}
}

void	ft_dist_order(t_all *all)
{
	int		i;
	int		j;
	double	tmp;

	ft_dist_order2(all);
	i = -1;
	while (++i < all->spr.nbspr)
	{
		j = -1;
		while (++j < all->spr.nbspr - 1)
		{
			if (all->spr.dist[j] < all->spr.dist[j + 1])
			{
				tmp = all->spr.dist[j];
				all->spr.dist[j] = all->spr.dist[j + 1];
				all->spr.dist[j + 1] = tmp;
				tmp = all->spr.order[j];
				all->spr.order[j] = all->spr.order[j + 1];
				all->spr.order[j + 1] = (int)tmp;
			}
		}
	}
}

void	ft_calculs(t_all *all, int i)
{
	all->spr.spritex = all->sprite[all->spr.order[i]].x - all->ray.posx;
	all->spr.spritey = all->sprite[all->spr.order[i]].y - all->ray.posy;
	all->spr.invdet = 1.0 / (all->ray.planx * all->ray.diry -
			all->ray.dirx * all->ray.plany);
	all->spr.transformx = all->spr.invdet * (all->ray.diry *
			all->spr.spritex - all->ray.dirx * all->spr.spritey);
	all->spr.transformy = all->spr.invdet * (-all->ray.plany *
			all->spr.spritex + all->ray.planx * all->spr.spritey);
	all->spr.spritescreenx = (int)((all->win.x / 2) * (1 + all->spr.transformx
				/ all->spr.transformy));
	all->spr.spriteheight = abs((int)(all->win.y / (all->spr.transformy)));
	all->spr.drawstarty = -all->spr.spriteheight / 2 + all->win.y / 2;
	if (all->spr.drawstarty < 0)
		all->spr.drawstarty = 0;
	all->spr.drawendy = all->spr.spriteheight / 2 + all->win.y / 2;
	if (all->spr.drawendy >= all->win.y)
		all->spr.drawendy = all->win.y;
	all->spr.spritewidth = abs((int)(all->win.y / (all->spr.transformy)));
	all->spr.drawstartx = -all->spr.spritewidth / 2 + all->spr.spritescreenx;
	if (all->spr.drawstartx < 0)
		all->spr.drawstartx = 0;
	all->spr.drawendx = all->spr.spritewidth / 2 + all->spr.spritescreenx;
	if (all->spr.drawendx >= all->win.x)
		all->spr.drawendx = all->win.x;
}

void	ft_draw_spr(t_all *all, int y, int texx, int stripe)
{
	int		d;
	int		texy;

	while (y < all->spr.drawendy)
	{
		d = (y) * 256 - all->win.y * 128 + all->spr.spriteheight * 128;
		texy = ((d * all->texture[4].height) / all->spr.spriteheight) / 256;
		if (all->texture[4].addr[texy * all->texture[4].line_length / 4 +
				texx] != -16777216)
		{
			all->data.addr[y * all->data.line_length / 4 + stripe] =
				all->texture[4].addr[texy * all->texture[4].line_length /
				4 + texx];
		}
		y++;
	}
}

void	ft_spr(t_all *all)
{
	int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	ft_dist_order(all);
	while (++i < all->spr.nbspr)
	{
		ft_calculs(all, i);
		stripe = all->spr.drawstartx;
		while (stripe < all->spr.drawendx)
		{
			texx = (int)(256 * (stripe - (-all->spr.spritewidth / 2 +
							all->spr.spritescreenx)) * all->texture[4].width
					/ all->spr.spritewidth) / 256;
			if (all->spr.transformy > 0 && stripe >= 0 && stripe < all->win.x
					&& all->spr.transformy < all->spr.zbuffer[stripe])
			{
				y = all->spr.drawstarty;
				ft_draw_spr(all, y, texx, stripe);
			}
			stripe++;
		}
	}
}
