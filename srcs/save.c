/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:11:24 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/09 16:05:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** BM, 424D en hexadécimal, indique qu'il s'agit d'un Bitmap Windows
** Taille totale du fichier en octets (codée sur 4 octets)
** Un champ réservé (sur 4 octets)
** Offset de l'image  : adresse relative du début des informations concernant
** l'image par rapport au début du fichier
*/

void	ft_bmp_header(t_all *all, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * all->resx * all->resy;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 4);
	tmp = 54;
	write(fd, &tmp, 4);
}

/*
** taille de l'entête de l'image
** nb de pixels horizontaux
** nb de pixels verticaux
** nb de plans (toujours = 1 et sur 2 octets)
** nb de bits utilisés pour coder la couleur
** méthode de compression (0 car nn compressee)
*/

void	ft_bmp_information_header(t_all *all, int fd)
{
	int	tmp;
	
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

/*
** writes the bmp line by line before putting it in a window
** should the authorisation change ? - system("chmod 777 image.bmp"
*/

void	ft_save(t_all *all)
{
	int	fd;
	int	x;
	int	y;

	y = all->resy;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_error(all, 1, "Failed to create .bmp\n");
	ft_bmp_header(all, fd);
	ft_bmp_information_header(all, fd);
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
	ft_error(all, 0, "Quitting properly after saving image.bmp\n");
}

/*
**ft_save checks whether the argument --save is the 3rd arg;
*/

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
