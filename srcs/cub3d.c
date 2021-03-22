/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:24 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/22 09:39:26 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_parsing_map(char *filename, t_all *all)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(filename, O_RDONLY);
	if (!(all->map = malloc(sizeof(char*) * all->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, all);
		if (all->insidemap == 1 && ft_emptyline(str) == 0 &&
				all->count < all->nblines)
			all->emptyline = 1;
		if ((all->insidemap = ft_is_map(str, all)) == 1)
		{
			all->count++;
			ft_copy_map(str, all);
		}
		free(str);
	}
	close(fd);
	ft_init_sprite(all);
	return (0);
}

void	ft_parsing(char *filename, t_all *all)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if ((fd = open(filename, O_DIRECTORY)) != -1)
		ft_error(all, 1, "Argument is a directory\n");
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_error(all, 1, "Invalid .cub file\n");
	all->erreur = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, all);
		if (all->erreur == 2)
			ft_error(all, 1, "Parsing error\n");
		ft_color_resolution(&str, all);
		ft_texture(str, all);
		ft_map(str, all);
		free(str);
	}
	close(fd);
	if (all->sizeline == 0 || all->nblines == 0)
		ft_error(all, 1, "No Map\n");
	ft_parsing_map(filename, all);
}

int		ft_cub(char *str, t_all *all)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error(all, 1, "Invalid Map Name\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, all);
	else
		ft_error(all, 1, "Invalid Map Name\n");
	return (0);
}

int		main(int ac, char **av)
{
	t_all all;

	all.save = 0;
	ft_init(&all);
	if (ac == 2 || (ac == 3 && ft_check_save(av[2]) == 1))
	{
		if (ac == 3)
			all.save = 1;
		ft_cub(av[1], &all);
	}
	else
		printf("%sERROR\nInvalid Arguments.\n", RED);
}
