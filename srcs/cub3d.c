/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:24 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/07 16:13:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_map_parsing(char *filename, t_all *all)
{
	int		fd;
	int		gnl_ret;
	char	*line;

	gnl_ret = 1;
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (!(all->map = malloc(sizeof(char*) * all->nblines)))
		return (0);
	while (gnl_ret != 0)
	{
		gnl_ret = get_next_line(fd, &line, all);
		if (all->is_in_map == 1 && ft_empty_line(line) == 0 &&
				all->count < all->nblines)
			all->emptyline = 1;
		if ((all->is_in_map = ft_line_is_map(line, all)) == 1)
		{
			all->count++;
			ft_map_copy(line, all);
		}
		free(line);
	}
	close(fd);
	ft_init_sprite(all);
	return (0);
}

void	ft_line(t_all *all, char *line)
{
	int		i;

	i = 0;
	ft_skipspace(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(all, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		all->err = ft_texture(all, &all->no, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		all->err = ft_texture(all, &all->so, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		all->err = ft_texture(all, &all->we, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		all->err = ft_texture(all, &all->ea, line, &i);
	else if (line[i] == 'S' && line[i + 1] != 'O')
		all->err = ft_texture(all, &all->sp, line, &i);
	else if (line[i] == 'F')
		all->err = ft_colors(all, &all->f, line, &i);
	else if (line[i] == 'C')
		all->err = ft_colors(all, &all->c, line, &i);
	else if (line[i] != '1' && line[i] != '0' && line[i] != '2'
			&& line[i] > 32 && line[i] <= 126)
		all->err = 3;
}

void	ft_parse(char *filename, t_all *all)
{
	int		ret;
	int		fd;
	char	*line;

	line = NULL;
	if ((fd = open(filename, O_DIRECTORY)) != -1)
		ft_error(all, 1, "Argument is a directory\n");
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_error(all, 1, "Invalid .cub file\n");
	all->err = 1;
	ret = 1;
	while (ret != 0 && all->err < 2)
	{
		ret = get_next_line(fd, &line, all);
		ft_line(all, line);
		ft_map(line, all);
		free(line);
	}
	close(fd);
	if (all->err >= 2)
		ft_parsing_error(all);
	if (all->sizeline == 0 || all->nblines == 0)
		ft_error(all, 1, "No Map\n");
	ft_map_parsing(filename, all);
}


int		main(int ac, char **av)
{
	t_all	all;
	int i;

	i = 0;
	ft_init(&all);
	if (ac == 2 || (ac == 3 && ft_check_save(av[2]) == 1))
	{
		if (ac == 3)
			all.save = 1;
		while (av[1][i])
			i++;
		if (i > 4 && av[1][i - 1] == 'b' && av[1][i - 2] == 'u' && av[1][i - 3] == 'c'
			&& av[1][i - 4] == '.')
			ft_parse(av[1], &all);
		else
			ft_error(&all, 1, "Invalid Map Name\n");	
	}
	else
		ft_error(&all, 1, "Invalid Arguments\n");
}
