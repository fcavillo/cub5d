#include "../includes/cub3d.h" 

void	ft_verify_errors(t_all *all)
{
	if (ft_murs(all) == 1)
		ft_error(all, "Map non entouree de 1\n");
	if (all->depart == 'x')
		ft_error(all, "Pas de joueur\n");
	if (all->indicateur2 != 6)
		ft_error(all, "Mauvaises donnees F ou C\n");
	if (all->multijoueurs == 1)
		ft_error(all, "Plus d'un joueur\n");
	if (all->lignevide == 1)
		ft_error(all, "Ligne vide dans la map\n");
	if (all->wrongcharmap == 2)
		ft_error(all, "Caractere incorrect dans la map\n");
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

void	ft_error(t_all *all, char *str)
{
	int i;

	i = -1;
	all->indicateur3 = 1;
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
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
		while (++i < all->nblines)
			free(all->map[i]);
	}
	ft_error2(all);
}

int		ft_exit(t_all *all)
{
	if (all->indicateur3 == 0)
		ft_error(all, "Non jrigole\n");
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
