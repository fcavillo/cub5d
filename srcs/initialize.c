#include "../includes/cub3d.h"

void	ft_init_more(t_all *all)
{
	all->start_pos = 'x';
	all->indicateur2 = 0;
	all->indicateur3 = 0;
	all->data.img = NULL;
	all->texture[0].img = NULL;
	all->texture[1].img = NULL;
	all->texture[2].img = NULL;
	all->texture[3].img = NULL;
	all->texture[4].img = NULL;
	all->data.mlx_win = NULL;
	all->map = NULL;
	all->s.order = NULL;
	all->s.dist = NULL;
	all->s.zbuffer = NULL;
	all->sxy = NULL;
}

void	ft_init_dir(t_all *all)
{
	if (all->start_pos == 'N')
		all->ray.dirx = -1;
	if (all->start_pos == 'S')
		all->ray.dirx = 1;
	if (all->start_pos == 'E')
		all->ray.diry = 1;
	if (all->start_pos == 'W')
		all->ray.diry = -1;
	if (all->start_pos == 'N')
		all->ray.plany = 0.66;
	if (all->start_pos == 'S')
		all->ray.plany = -0.66;
	if (all->start_pos == 'E')
		all->ray.planx = 0.66;
	if (all->start_pos == 'W')
		all->ray.planx = -0.66;
}

void	ft_init_more3(t_all *all)
{
	if (all->ray.raydiry == 0)
		all->ray.deltadistx = 0;
	else if (all->ray.raydirx == 0)
		all->ray.deltadistx = 1;
	else
		all->ray.deltadistx = sqrt(1 + (all->ray.raydiry
			* all->ray.raydiry) / (all->ray.raydirx *
			all->ray.raydirx));
	if (all->ray.raydirx == 0)
		all->ray.deltadisty = 0;
	else if (all->ray.raydiry == 0)
		all->ray.deltadisty = 1;
	else
		all->ray.deltadisty = sqrt(1 + (all->ray.raydirx *
			all->ray.raydirx) / (all->ray.raydiry *
			all->ray.raydiry));
}

void	ft_atoi3_check(const char *str, t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != ',')
		i++;
	if (str[i] == ',')
		j = 1;
	i++;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		all->erreur = 2;
	if (ft_nb_virgule(str) != 2)
		all->erreur = 2;
}

int		ft_lignevide(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' &&
				str[i] != '\n' && str[i] != '\r' && str[i] != '\v'
				&& str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}
