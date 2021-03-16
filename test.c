/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:45:14 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/04 10:37:03 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub3d.h"

void test(t_all *all)
{
    int i;

    i = 0;
    printf("Resolution = %d, %d\n", all->win.x, all->win.y);
    printf("text.n = %s\n", all->tex.n);
    printf("text.s = %s\n", all->tex.s);
    printf("text.e = %s\n", all->tex.e);
    printf("text.w = %s\n", all->tex.w);
    printf("text.spr = %s\n", all->tex.spr);
    printf("color.c = %u\n", all->tex.c);   
    printf("color.f = %u\n\n", all->tex.f);
    while (i < all->map.y && all->err2 != 100)
    {
        printf("%s\n", all->map.cub[i]);
        i++;
    }
    printf("\nSPAWN :\norientation : %c x : %d y : %d\n", all->map.spawn_orientation, all->map.spawn_x, all->map.spawn_y);
    printf("map_x = %d\nmap_y = %d\n", all->map.x, all->map.y);
    printf("Sprite number = %d\n", all->map.spr_nb);
}