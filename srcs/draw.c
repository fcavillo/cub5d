/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:31:23 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/16 11:57:09 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_tex(t_all *all)
{
	if (all->ray.side == 0 && all->ray.raydirx < 0)
		all->tex.texdir = 0;
	if (all->ray.side == 0 && all->ray.raydirx >= 0)
		all->tex.texdir = 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->tex.texdir = 2;
	if (all->ray.side == 1 && all->ray.raydiry >= 0)
		all->tex.texdir = 3;
	if (all->ray.side == 0)
		all->tex.wallx = all->ray.posy + all->ray.perpwalldist \
						* all->ray.raydiry;
	else
		all->tex.wallx = all->ray.posx + all->ray.perpwalldist \
						* all->ray.raydirx;
	all->tex.wallx -= floor((all->tex.wallx));
}

void    ft_texture_draw(t_all *all, int x, int y)
{
    y = all->ray.drawstart - 1;
    ft_init_tex(all);
	all->tex.step = 1.0 * all->texture[0].height / all->ray.lineheight;
	all->tex.texx = (int)(all->tex.wallx * (double)all->texture
			[all->tex.texdir].width);
	if (all->ray.side == 0 && all->ray.raydirx > 0)
		all->tex.texx = all->texture[all->tex.texdir].width -
			all->tex.texx - 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->tex.texx = all->texture[all->tex.texdir].width -
			all->tex.texx - 1;
	all->tex.texpos = (all->ray.drawstart - all->win.y / 2 +
			all->ray.lineheight / 2) * all->tex.step;
	while (++y <= all->ray.drawend)
	{
		all->tex.texy = (int)all->tex.texpos &
			(all->texture[all->tex.texdir].height - 1);
		all->tex.texpos += all->tex.step;
		if (y < all->win.y && x < all->win.x)
			all->data.addr[y * all->data.line_length / 4 + x] =
				all->texture[all->tex.texdir].addr[all->tex.texy *
					all->texture[all->tex.texdir].line_length /
					4 + all->tex.texx];
	}
}

void    ft_column_color(t_all *all)
{
    int i;
    int j;

    j = 0;
    all->ray.drawend = all->win.y - all->ray.drawstart;
    i = all->ray.drawend;
    while (j < all->ray.drawstart)
    {
        all->data.addr[j * all->data.line_length / 4 + all->ray.x] = all->tex.c;
        j++;
    }
    if (j <= all->ray.drawend)
        ft_texture_draw(all, all->ray.x, j);
    j = i;
    while (++j < all->win.y)
        all->data.addr[j * all->data.line_length / 4 + all->ray.x] = all->tex.f;    
}