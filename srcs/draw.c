#include "../includes/cub3d.h"

int		ft_key_press(int key, t_all *all) 
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
	return (1);
}

int		ft_key_release(int key, t_all *all)
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
	return (1);
}

int		ft_color_column(t_all *all)
{
	int j;
	int i;

	j = -1;
	all->ray.drawend = all->ry - all->ray.drawstart;
	i = all->ray.drawend;
	while (++j < all->ray.drawstart)
		all->data.addr[j * all->data.line_length / 4 +
			all->ray.x] = all->c;
	if (j <= all->ray.drawend)
		ft_draw_texture(all, all->ray.x, j);
	j = i;
	while (++j < all->ry)
		all->data.addr[j * all->data.line_length / 4 +
			all->ray.x] = all->f;
	return (0);
}

void	ft_draw_texture(t_all *all, int x, int y)
{
	y = all->ray.drawstart - 1;
	ft_init_texture(all);
	all->tex.step = 1.0 * all->texture[0].height / all->ray.lineheight;
	all->tex.texx = (int)(all->tex.wallx * (double)all->texture
			[all->tex.texdir].width);
	if (all->ray.side == 0 && all->ray.raydirx > 0)
		all->tex.texx = all->texture[all->tex.texdir].width -
			all->tex.texx - 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->tex.texx = all->texture[all->tex.texdir].width -
			all->tex.texx - 1;
	all->tex.texpos = (all->ray.drawstart - all->ry / 2 +
			all->ray.lineheight / 2) * all->tex.step;
	while (++y <= all->ray.drawend)
	{
		all->tex.texy = (int)all->tex.texpos &
			(all->texture[all->tex.texdir].height - 1);
		all->tex.texpos += all->tex.step;
		if (y < all->ry && x < all->rx)
			all->data.addr[y * all->data.line_length / 4 + x] =
				all->texture[all->tex.texdir].addr[all->tex.texy *
					all->texture[all->tex.texdir].line_length /
					4 + all->tex.texx];
	}
}
