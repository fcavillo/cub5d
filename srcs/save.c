/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:24 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/24 14:33:05 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_header(t_all *all, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * all->resx * all->resy;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &all->resx, 4);
	write(fd, &all->resy, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &all->data.bits_per_pixel, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	ft_save(t_all *all)
{
	int	fd;
	int	x;
	int	y;

	y = all->resy;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_error(all, 1, "Failing to create .bmp\n");
	ft_header(all, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < all->resx)
		{
			write(fd, &all->data.addr[y * all->data.line_length / 4 + x],
				4);
			x++;
		}
		y--;
	}
	system("chmod 777 image.bmp");
	ft_error(all, 0, "Quitting properly after saving bmp\n");
}

int		ft_check_save(char *str)
{
	int i;

	i = 0;
	if (str[0] == '-' && str[1] == '-' && str[2] == 's' && str[3] == 'a'
		&& str[4] == 'v' && str[5] == 'e' && str[6] == '\0'
		&& ft_strlen(str) == 6)
		return (1);
	return (0);
}

