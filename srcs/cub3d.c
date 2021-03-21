#include "../includes/cub3d.h"

int		ft_parsing_map(char *fichier, t_all *all)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(fichier, O_RDONLY);
	if (!(all->map = malloc(sizeof(char*) * all->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, all);
		if (all->insidemap == 1 && ft_lignevide(str) == 0 &&
				all->count < all->nblines)
			all->lignevide = 1;
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

void	ft_parsing(char *fichier, t_all *all)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if ((fd = open(fichier, O_DIRECTORY)) != -1)
		ft_error(all, 1, "Invalide : is a directory\n");
	if ((fd = open(fichier, O_RDONLY)) == -1)
		ft_error(all, 1, "Fichier .cub invalide\n");
	all->erreur = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, all);
		if (all->erreur == 2)
			ft_error(all, 1, "La partie parsing detecte une erreur\n");
		ft_color_resolution(&str, all);
		ft_texture(str, all);
		ft_map(str, all);
		free(str);
	}
	close(fd);
	if (all->sizeline == 0 || all->nblines == 0)
		ft_error(all, 1, "Map absente\n");
	ft_parsing_map(fichier, all);
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
			ft_error(all, 1, "Nom de la map invalide\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, all);
	else
		ft_error(all, 1, "Nom de la map invalide\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_all all;

	all.save = 0;
	ft_initialisation(&all);
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			all.save = 1;
		ft_cub(argv[1], &all);
	}
	else
		write(1, "Error\nArguments invalides\n", 30);
}
