/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:53 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/24 11:59:10 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_press_key(int key, t_all *all)
{
	if (key == KEY_FORWARD)
		all->data.forward = 1;
	else if (key == KEY_BACK)
		all->data.back = 1;
	else if (key == KEY_LEFT)
		all->data.left = 1;
	else if (key == KEY_RIGHT)
		all->data.right = 1;
	else if (key == KEY_ROTATE_LEFT)
		all->data.rotate_left = 1;
	else if (key == KEY_ROTATE_RIGHT)
		all->data.rotate_right = 1;
	else if (key == KEY_ESCAPE)
		ft_error(all, 0, "Quitting properly\n");
	return (0);
}

int		ft_release_key(int key, t_all *all)
{
	if (key == KEY_FORWARD)
		all->data.forward = 0;
	else if (key == KEY_BACK)
		all->data.back = 0;
	else if (key == KEY_LEFT)
		all->data.left = 0;
	else if (key == KEY_RIGHT)
		all->data.right = 0;
	else if (key == KEY_ROTATE_LEFT)
		all->data.rotate_left = 0;
	else if (key == KEY_ROTATE_RIGHT)
		all->data.rotate_right = 0;
	return (0);
}
