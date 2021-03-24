/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:33 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/24 08:41:55 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_texture(t_all *all, int x, int y)
{
	y = all->ray.drawstart - 1;
	ft_init_texture(all);
	all->tex.step = 1.0 * all->texture[0].height / all->ray.lineheight;
	all->tex.texx = (int)(all->tex.wallx * (double)all->texture
			[all->tex.texdir].width);
	if (all->ray.side == 0 && all->ray.raydirx > 0)
		all->tex.texx = all->texture[all->tex.texdir].width -
			all->tex.texx - 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->tex.texx = all->texture[all->tex.texdir].width -
			all->tex.texx - 1;
	all->tex.texpos = (all->ray.drawstart - all->resy / 2 +
			all->ray.lineheight / 2) * all->tex.step;
	while (++y <= all->ray.drawend)
	{
		all->tex.texy = (int)all->tex.texpos &
			(all->texture[all->tex.texdir].height - 1);
		all->tex.texpos += all->tex.step;
		if (y < all->resy && x < all->resx)
			all->data.addr[y * all->data.line_length / 4 + x] =
				all->texture[all->tex.texdir].addr[all->tex.texy *
					all->texture[all->tex.texdir].line_length /
					4 + all->tex.texx];
	}
}

int		ft_column_color(t_all *all)
{
	int j;
	int i;

	j = -1;
	all->ray.drawend = all->resy - all->ray.drawstart;
	i = all->ray.drawend;
	while (++j < all->ray.drawstart)
		all->data.addr[j * all->data.line_length / 4 +
			all->ray.x] = all->c;
	if (j <= all->ray.drawend)
		ft_draw_texture(all, all->ray.x, j);
	j = i;
	while (++j < all->resy)
		all->data.addr[j * all->data.line_length / 4 +
			all->ray.x] = all->f;
	return (0);
}

