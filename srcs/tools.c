#include "../includes/cub3d.h"

int		ft_strlen2(char *str)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

int		ft_charinstr(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_depart(char c, t_all *all, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (all->depart != 'x')
			all->multijoueurs = 1;
		all->depart = c;
		all->dx = i;
		all->dy = j;
		return (1);
	}
	return (0);
}

int		ft_murs_util(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	ft_initialisation(t_all *all)
{
	all->no = NULL;
	all->so = NULL;
	all->we = NULL;
	all->ea = NULL;
	all->sp = NULL;
	all->f = -1;
	all->c = -1;
	all->rx = 0;
	all->ry = 0;
	all->nblines = 0;
	all->sizeline = 0;
	all->map = NULL;
	all->dx = 0;
	all->dy = 0;
	all->multijoueurs = 0;
	all->lignevide = 0;
	all->insidemap = 0;
	all->count = 0;
	all->sum = 0;
	all->wrongcharmap = 0;
	ft_init_more(all);
}