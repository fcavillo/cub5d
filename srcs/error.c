/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:13:58 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/18 10:40:45 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_free_mlx(t_all *all)
{
	ft_error(all, "MLX error?\n");
	if (all->data.img)
		mlx_destroy_image(all->data.mlx_ptr, all->data.img);
	if (all->texture[0].img)
		mlx_destroy_image(all->data.mlx_ptr, all->texture[0].img);
	if (all->texture[1].img)
		mlx_destroy_image(all->data.mlx_ptr, all->texture[1].img);
	if (all->texture[2].img)
		mlx_destroy_image(all->data.mlx_ptr, all->texture[2].img);
	if (all->texture[3].img)
		mlx_destroy_image(all->data.mlx_ptr, all->texture[3].img);
	if (all->texture[4].img)
		mlx_destroy_image(all->data.mlx_ptr, all->texture[4].img);
	if (all->data.mlx_win)
		mlx_destroy_window(all->data.mlx_ptr, all->data.mlx_win);
	exit(0);
}

void    free_all_2(t_all *all)
{
	if (all->spr.order)
		free(all->spr.order);
	if (all->spr.dist)
		free(all->spr.dist);
	if (all->spr.zbuffer)
		free(all->spr.zbuffer);
	if (all->sprite)
		free(all->sprite);

	ft_free_mlx(all);
}

void	free_all(t_all *all)
{
	int i;

	i = 0;
	if (all->err2 != 100)
	{
		if (all->tex.s)
			free(all->tex.s);
		if (all->tex.n)
			free(all->tex.n);
		if (all->tex.e)
			free(all->tex.e);
		if (all->tex.w)
			free(all->tex.w);
		if (all->tex.spr)
			free(all->tex.spr);
		if (all->map.cub)
			while (i < all->map.y)
			{
				free(all->map.cub[i]);
				i++;
			}
		if (all->map.cub)
			free(all->map.cub);
		free_all_2(all);
	}
}





void    ft_error(t_all *all, char *str)
{
	if (all->err2 == 0)
	{
		printf("%sError\n%s", RED, str);
		all->err2 = 100;
		free_all(all);
	}
//    ft_error_2(t_all *all);
}

void		ft_check_errors(t_all *all)
{
	if (all->map.spawn_nb == 0)
		ft_error(all, "There is no player spawn\n");
	if (all->map.spawn_nb >= 2)
		ft_error(all, "Too many players\n");
	if (all->map.emptyline == 1)
		ft_error(all, "Empty line in the map\n");
	
}