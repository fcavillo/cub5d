#include "../includes/cub3d.h"

int		ft_key_press(int keycode, t_all *all) 
{
	if (keycode == FORWARD_W_Z)
		all->data.forward = 1;
	else if (keycode == BACK_S_S)
		all->data.back = 1;
	else if (keycode == LEFT_A_Q)
		all->data.left = 1;
	else if (keycode == RIGHT_D_D)
		all->data.right = 1;
	else if (keycode == ROTATE_LEFT)
		all->data.rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		all->data.rotate_right = 1;
	else if (keycode == 65307)
		ft_error(all, 0, "Quitting properly\n");
	return (1);
}

int		ft_key_release(int keycode, t_all *all)
{
	if (keycode == FORWARD_W_Z)
		all->data.forward = 0;
	else if (keycode == BACK_S_S)
		all->data.back = 0;
	else if (keycode == LEFT_A_Q)
		all->data.left = 0;
	else if (keycode == RIGHT_D_D)
		all->data.right = 0;
	else if (keycode == ROTATE_LEFT)
		all->data.rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
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
	all->t.step = 1.0 * all->texture[0].height / all->ray.lineheight;
	all->t.texx = (int)(all->t.wallx * (double)all->texture
			[all->t.texdir].width);
	if (all->ray.side == 0 && all->ray.raydirx > 0)
		all->t.texx = all->texture[all->t.texdir].width -
			all->t.texx - 1;
	if (all->ray.side == 1 && all->ray.raydiry < 0)
		all->t.texx = all->texture[all->t.texdir].width -
			all->t.texx - 1;
	all->t.texpos = (all->ray.drawstart - all->ry / 2 +
			all->ray.lineheight / 2) * all->t.step;
	while (++y <= all->ray.drawend)
	{
		all->t.texy = (int)all->t.texpos &
			(all->texture[all->t.texdir].height - 1);
		all->t.texpos += all->t.step;
		if (y < all->ry && x < all->rx)
			all->data.addr[y * all->data.line_length / 4 + x] =
				all->texture[all->t.texdir].addr[all->t.texy *
					all->texture[all->t.texdir].line_length /
					4 + all->t.texx];
	}
}
