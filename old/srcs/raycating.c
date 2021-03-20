/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:09:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/19 13:27:03 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    ft_set_textures_addr(t_all *all)
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


void    ft_set_textures(t_all *all)
{
    if (!(all->texture[0].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->tex.n, &(all->texture[0].width),
					&(all->texture[0].height))))
                    ft_error(all, "Invalid North texture\n");
    if (!(all->texture[1].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->tex.s, &(all->texture[1].width),
					&(all->texture[1].height))))
                    ft_error(all, "Invalid South texture\n");
    if (!(all->texture[2].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->tex.e, &(all->texture[2].width),
					&(all->texture[2].height))))
                    ft_error(all, "Invalid East texture\n");
    if (!(all->texture[3].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->tex.w, &(all->texture[3].width),
					&(all->texture[3].height))))
                    ft_error(all, "Invalid West texture\n");
    if (!(all->texture[4].img = mlx_xpm_file_to_image(all->data.mlx_ptr,
					all->tex.spr, &(all->texture[4].width),
					&(all->texture[4].height))))
                    ft_error(all, "Invalid Sprite texture\n");
    ft_set_textures_addr(all);
}

void     ft_set_window_size(t_all *all)
{
    if (all->data.screenx > all->win.x)
        all->win.x = all->data.screenx;    
    if (all->data.screeny > all->win.y)
        all->win.y = all->data.screeny;    
}

void    ft_save(t_all *all)
{
    printf("SAVE = %d\n", all->save);
}

int     ft_ray(t_all *all)
{
    ft_ray_init(all);
    if (!(all->data.mlx_ptr = mlx_init()))
        ft_error(all, "Mlx init failed\n");
    mlx_get_screen_size(all->data.mlx_ptr, &all->data.screenx, &all->data.screeny);
    ft_set_window_size(all);
    ft_set_textures(all);
    all->data.img = mlx_new_image(all->data.mlx_ptr, all->win.x, all->win.y);
    all->data.addr = (int *)mlx_get_data_addr(all->data.img, 
        &all->data.bits_per_pixel, &all->data.line_length, &all->data.endian);
    if (all->save == 1)
        ft_save(all); //A FAIRE
    all->data.mlx_win = mlx_new_window(all->data.mlx_ptr, all->win.x, all->win.y,
            "Cuba");
    all->data.img2 = mlx_new_image(all->data.mlx_ptr, all->win.x, all->win.y);
    all->data.addr2 = (int *)mlx_get_data_addr(all->data.img, 
        &all->data.bits_per_pixel, &all->data.line_length, &all->data.endian); 
    mlx_hook(all->data.mlx_win, 33, 1L << 17, ft_free_mlx, all);   //whut
    mlx_hook(all->data.mlx_win, 2, 1L <<0, ft_press_key, all);
    mlx_loop_hook(all->data.mlx_ptr, ft_raycast, all);
    mlx_hook(all->data.mlx_win, 3, 1L << 1, ft_release_key, all);
    mlx_loop(all->data.mlx_ptr);    
    return (0);
}