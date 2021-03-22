/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:37 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/22 09:10:38 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h" 

void	ft_verify_errors(t_all *all)
{
	if (ft_murs(all) == 1)
		ft_error(all, 1, "Map should be surrounded by 1\n");
	if (all->start_pos == 'x')
		ft_error(all, 1, "No spawn point\n");
	if (all->indicateur2 != 6)
		ft_error(all, 1, "Wrong C or F color\n");
	if (all->spawn_nb == 1)
		ft_error(all, 1, "Too many spawn points\n");
	if (all->emptyline == 1)
		ft_error(all, 1, "Empty line inside the Map\n");
	if (all->wrongcharmap == 2)
		ft_error(all, 1, "Incorrect char in Map\n");
}

void	ft_error2(t_all *all)
{
	if (all->map)
		free(all->map);
	if (all->s.order)
		free(all->s.order);
	if (all->s.dist)
		free(all->s.dist);
	if (all->sxy)
		free(all->sxy);
	if (all->s.zbuffer)
		free(all->s.zbuffer);
	ft_exit(all);
}

void	ft_error(t_all *all, int i, char *str)
{
	int j;

	j = -1;
	all->indicateur3 = 1;
	if(i == 1)
		printf("%sERROR\n", RED);
	printf("%s\n", str);
	if (all->no)
		free(all->no);
	if (all->so)
		free(all->so);
	if (all->we)
		free(all->we);
	if (all->ea)
		free(all->ea);
	if (all->sp)
		free(all->sp);
	if (all->map)
	{
		while (++j < all->nblines)
			free(all->map[j]);
	}
	ft_error2(all);
}

int		ft_exit(t_all *all)
{
	if (all->indicateur3 == 0)
		ft_error(all, 0, "Quitting properly\n");
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
