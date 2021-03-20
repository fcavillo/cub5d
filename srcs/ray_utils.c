#include "../includes/cub3d.h"

void	ft_stepsidedist(t_all *all)
{
	if (all->ray.raydirx < 0)
	{
		all->ray.stepx = -1;
		all->ray.sidedistx = (all->ray.posx - all->ray.mapx) \
							* all->ray.deltadistx;
	}
	else
	{
		all->ray.stepx = 1;
		all->ray.sidedistx = (all->ray.mapx + 1.0 - all->ray.posx) \
							* all->ray.deltadistx;
	}
	if (all->ray.raydiry < 0)
	{
		all->ray.stepy = -1;
		all->ray.sidedisty = (all->ray.posy - all->ray.mapy) \
							* all->ray.deltadisty;
	}
	else
	{
		all->ray.stepy = 1;
		all->ray.sidedisty = (all->ray.mapy + 1.0 - all->ray.posy) \
							* all->ray.deltadisty;
	}
	ft_incrementray(all);
}

void	ft_incrementray(t_all *all)
{
	while (all->ray.hit == 0)
	{
		if (all->ray.sidedistx < all->ray.sidedisty)
		{
			all->ray.sidedistx += all->ray.deltadistx;
			all->ray.mapx += all->ray.stepx;
			all->ray.side = 0;
		}
		else
		{
			all->ray.sidedisty += all->ray.deltadisty;
			all->ray.mapy += all->ray.stepy;
			all->ray.side = 1;
		}
		if (all->map[all->ray.mapx][all->ray.mapy] == '1')
			all->ray.hit = 1;
	}
	ft_drawstartend(all);
}

void	ft_drawstartend(t_all *all)
{
	if (all->ray.side == 0)
		all->ray.perpwalldist = ((double)all->ray.mapx - \
				all->ray.posx + (1 - (double)all->ray.
				stepx) / 2) / all->ray.raydirx;
	else
		all->ray.perpwalldist = ((double)all->ray.mapy - \
				all->ray.posy + (1 - (double)all->ray.
				stepy) / 2) / all->ray.raydiry;
	all->ray.lineheight = (int)(all->ry / all->ray.perpwalldist);
	all->ray.drawstart = -all->ray.lineheight / 2 + all->ry / 2;
	if (all->ray.drawstart < 0)
		all->ray.drawstart = 0;
	all->ray.drawend = all->ray.lineheight / 2 + all->ry / 2;
	if (all->ray.drawend >= all->ry || all->ray.drawend < 0)
		all->ray.drawend = all->ry - 1;
}

void	ft_swap(t_all *all)
{
	void *tmp;

	tmp = all->data.img;
	all->data.img = all->data.img2;
	all->data.img2 = tmp;
	tmp = all->data.addr;
	all->data.addr = all->data.addr2;
	all->data.addr2 = tmp;
}
