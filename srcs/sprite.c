#include "../includes/cub3d.h"

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

void	ft_calculs(t_all *all, int i)
{
	all->s.spritex = all->sxy[all->s.order[i]].x - all->ray.posx;
	all->s.spritey = all->sxy[all->s.order[i]].y - all->ray.posy;
	all->s.invdet = 1.0 / (all->ray.planx * all->ray.diry -
			all->ray.dirx * all->ray.plany);
	all->s.transformx = all->s.invdet * (all->ray.diry *
			all->s.spritex - all->ray.dirx * all->s.spritey);
	all->s.transformy = all->s.invdet * (-all->ray.plany *
			all->s.spritex + all->ray.planx * all->s.spritey);
	all->s.spritescreenx = (int)((all->rx / 2) * (1 + all->s.transformx
				/ all->s.transformy));
	all->s.spriteheight = abs((int)(all->ry / (all->s.transformy)));
	all->s.drawstarty = -all->s.spriteheight / 2 + all->ry / 2;
	if (all->s.drawstarty < 0)
		all->s.drawstarty = 0;
	all->s.drawendy = all->s.spriteheight / 2 + all->ry / 2;
	if (all->s.drawendy >= all->ry)
		all->s.drawendy = all->ry;
	all->s.spritewidth = abs((int)(all->ry / (all->s.transformy)));
	all->s.drawstartx = -all->s.spritewidth / 2 + all->s.spritescreenx;
	if (all->s.drawstartx < 0)
		all->s.drawstartx = 0;
	all->s.drawendx = all->s.spritewidth / 2 + all->s.spritescreenx;
	if (all->s.drawendx >= all->rx)
		all->s.drawendx = all->rx;
}

void	ft_draw_spr(t_all *all, int y, int texx, int stripe)
{
	int		d;
	int		texy;

	while (y < all->s.drawendy)
	{
		d = (y) * 256 - all->ry * 128 + all->s.spriteheight * 128;
		texy = ((d * all->texture[4].height) / all->s.spriteheight) / 256;
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

void	ft_sprite(t_all *all)
{
	int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	ft_dist_order(all);
	while (++i < all->s.nbspr)
	{
		ft_calculs(all, i);
		stripe = all->s.drawstartx;
		while (stripe < all->s.drawendx)
		{
			texx = (int)(256 * (stripe - (-all->s.spritewidth / 2 +
							all->s.spritescreenx)) * all->texture[4].width
					/ all->s.spritewidth) / 256;
			if (all->s.transformy > 0 && stripe >= 0 && stripe < all->rx
					&& all->s.transformy < all->s.zbuffer[stripe])
			{
				y = all->s.drawstarty;
				ft_draw_spr(all, y, texx, stripe);
			}
			stripe++;
		}
	}
}