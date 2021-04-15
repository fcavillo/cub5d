/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:28 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/15 17:16:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** for each sprite, assign a distance from the sqr of x and y
*/

void	ft_dist_order2(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->s.nbspr)
	{
		all->s.order[i] = i;
		all->s.dist[i] = ((all->ray.posx - all->sxy[i].x) *
				(all->ray.posx - all->sxy[i].x) + (all->ray.posy -
					all->sxy[i].y) * (all->ray.posy - all->sxy[i].y));
	}
}

/*
** sort sprites from far to close
** set order and distance accordingly
*/

void	ft_dist_order(t_all *all)
{
	int		i;
	int		j;
	double	tmp;

	ft_dist_order2(all);
	i = -1;
	while (++i < all->s.nbspr)
	{
		j = -1;
		while (++j < all->s.nbspr - 1)
		{
			if (all->s.dist[j] < all->s.dist[j + 1])
			{
				tmp = all->s.dist[j];
				all->s.dist[j] = all->s.dist[j + 1];
				all->s.dist[j + 1] = tmp;
				tmp = all->s.order[j];
				all->s.order[j] = all->s.order[j + 1];
				all->s.order[j + 1] = (int)tmp;
			}
		}
	}
}

/*
** sets spriteX and Y to the relative position of the sprite to player
** sets inved, transformX and Y to 
*/

void	ft_calcul(t_all *all, int i)
{
	all->s.spritex = all->sxy[all->s.order[i]].x - all->ray.posx;
	all->s.spritey = all->sxy[all->s.order[i]].y - all->ray.posy;
	all->s.invdet = 1.0 / (all->ray.planx * all->ray.diry -
			all->ray.dirx * all->ray.plany);
	all->s.transformx = all->s.invdet * (all->ray.diry *
			all->s.spritex - all->ray.dirx * all->s.spritey);
	all->s.transformy = all->s.invdet * (-all->ray.plany *
			all->s.spritex + all->ray.planx * all->s.spritey);
	all->s.spritescreenx = (int)((all->resx / 2) * (1 + all->s.transformx
				/ all->s.transformy));
	all->s.spriteheight = abs((int)(all->resy / (all->s.transformy)));      //calculate height of the sprite on screen
	all->s.drawstarty = -all->s.spriteheight / 2 + all->resy / 2;
	if (all->s.drawstarty < 0)
		all->s.drawstarty = 0;
	all->s.drawendy = all->s.spriteheight / 2 + all->resy / 2;
	if (all->s.drawendy >= all->resy)
		all->s.drawendy = all->resy;
	all->s.spritewidth = abs((int)(all->resy / (all->s.transformy)));      //calculate width of the sprite
	all->s.drawstartx = -all->s.spritewidth / 2 + all->s.spritescreenx;
	if (all->s.drawstartx < 0)
		all->s.drawstartx = 0;
	all->s.drawendx = all->s.spritewidth / 2 + all->s.spritescreenx;
	if (all->s.drawendx >= all->resx)
		all->s.drawendx = all->resx;
}

void	ft_draw_spr(t_all *all, int y, int texx, int drawpix)
{
	int		d;
	int		texy;

	while (y < all->s.drawendy)
	{
		d = (y) * 256 - all->resy * 128 + all->s.spriteheight * 128;
		texy = ((d * all->texture[4].height) / all->s.spriteheight) / 256;
		if (all->texture[4].addr[texy * all->texture[4].line_length / 4 +
				texx] != -16777216)
		{
			all->data.addr[y * all->data.line_length / 4 + drawpix] =
				all->texture[4].addr[texy * all->texture[4].line_length /
				4 + texx];
		}
		y++;
	}
}

/*
** dist_order sorts sprites from far to close
*/

void	ft_sprite(t_all *all)
{
	int i;
	int y;
	int drawpix;
	int texx;

	i = -1;
	ft_dist_order(all);
	while (++i < all->s.nbspr)
	{
		ft_calcul(all, i);
		drawpix = all->s.drawstartx;
		while (drawpix < all->s.drawendx)
		{
			texx = (int)(256 * (drawpix - (-all->s.spritewidth / 2 +
							all->s.spritescreenx)) * all->texture[4].width
					/ all->s.spritewidth) / 256;
			if (all->s.transformy > 0 && drawpix >= 0 && drawpix < all->resx
					&& all->s.transformy < all->s.zbuffer[drawpix])
			{
				y = all->s.drawstarty;
				ft_draw_spr(all, y, texx, drawpix);
			}
			drawpix++;
		}
	}
}
