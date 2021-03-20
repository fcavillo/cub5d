#include "../includes/cub3d.h"

void	ft_get_texture_adress(t_all *all)
{
	all->texture[0].addr = (int *)mlx_get_data_addr(all->texture[0].img,
			&all->texture[0].bits_per_pixel,
			&all->texture[0].line_length, &all->texture[0].endian);
	all->texture[1].addr = (int *)mlx_get_data_addr(all->texture[1].img,
			&all->texture[1].bits_per_pixel,
			&all->texture[1].line_length, &all->texture[1].endian);
	all->texture[2].addr = (int *)mlx_get_data_addr(all->texture[2].img,
			&all->texture[2].bits_per_pixel,
			&all->texture[2].line_length, &all->texture[2].endian);
	all->texture[3].addr = (int *)mlx_get_data_addr(all->texture[3].img,
			&all->texture[3].bits_per_pixel,
			&all->texture[3].line_length, &all->texture[3].endian);
	all->texture[4].addr = (int *)mlx_get_data_addr(all->texture[4].img,
			&all->texture[4].bits_per_pixel,
			&all->texture[4].line_length, &all->texture[4].endian);
}

void	ft_get_texture(t_all *all)
{
	if (!(all->texture[0].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->no, &(all->texture[0].width),
					&(all->texture[0].height))))
		ft_error(all, "Texture SO\n");
	if (!(all->texture[1].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->so, &(all->texture[1].width),
					&(all->texture[1].height))))
		ft_error(all, "Texture NO\n");
	if (!(all->texture[2].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->we, &(all->texture[2].width),
					&(all->texture[2].height))))
		ft_error(all, "Texture EA\n");
	if (!(all->texture[3].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->ea, &(all->texture[3].width),
					&(all->texture[3].height))))
		ft_error(all, "Texture WE\n");
	if (!(all->texture[4].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->sp, &(all->texture[4].width),
					&(all->texture[4].height))))
		ft_error(all, "Texture S\n");
	ft_get_texture_adress(all);
}

int		ft_raycasting(t_all *all)
{
	all->ray.x = 0;
	while (all->ray.x < all->rx)
	{
		ft_initialisation3(all);
		ft_stepsidedist(all);
		ft_color_column(all);
		all->s.zbuffer[all->ray.x] = all->ray.perpwalldist;
		all->ray.x++;
	}
	ft_sprite(all);
	if (all->save == 1)
		ft_save(all);
	mlx_put_image_to_window(all->data.mlx_ptr, all->data.mlx_win,
			all->data.img, 0, 0);
	ft_forward_back(all);
	ft_left_right(all);
	ft_rotate_right_left(all);
	ft_swap(all);
	return (0);
}

int		ft_mlx(t_all *all)
{
	ft_initialisation2(all);
	if (!(all->data.mlx_ptr = mlx_init()))
		ft_error(all, "Mlx init impossible\n");
	mlx_get_screen_size(all->data.mlx_ptr, &all->screenx, &all->screeny);
	all->rx = (all->rx > all->screenx) ? all->screenx : all->rx;
	all->ry = (all->ry > all->screeny) ? all->screeny : all->ry;
	ft_get_texture(all);
	all->data.img = mlx_new_image(all->data.mlx_ptr, all->rx, all->ry);
	all->data.addr = (int *)mlx_get_data_addr(all->data.img, &all->data.
			bits_per_pixel, &all->data.line_length, &all->data.endian);
	if (all->save == 1)
		ft_raycasting(all);
	all->data.mlx_win = mlx_new_window(all->data.mlx_ptr, all->rx,
			all->ry, "Hello world!");
	all->data.img2 = mlx_new_image(all->data.mlx_ptr, all->rx, all->ry);
	all->data.addr2 = (int *)mlx_get_data_addr(all->data.img2, &all->
			data.bits_per_pixel, &all->data.line_length, &all->data.endian);
	mlx_hook(all->data.mlx_win, 33, 1L << 17, ft_exit, all);
	mlx_hook(all->data.mlx_win, 2, 1L << 0, ft_key_press, all);
	mlx_loop_hook(all->data.mlx_ptr, ft_raycasting, all);
	mlx_hook(all->data.mlx_win, 3, 1L << 1, ft_key_release, all);
	mlx_loop(all->data.mlx_ptr);
	return (0);
}
