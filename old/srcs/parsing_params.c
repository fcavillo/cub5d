/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:29:52 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/11 11:35:42 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int     ft_colors(t_all *all, int *color, char *line, int *i)
{
    int r;
    int g;
    int b;
    
    if (*color != -1)
    {
        all->err = 2;
        ft_error(all, "Color specified twice\n");
    }
    (*i)++;
    r = ft_atoi(line, i);
    if (ft_skipspace(line, i) && line[*i] == ',')
        (*i)++;
    g = ft_atoi(line, i);
    if (ft_skipspace(line, i) && line[*i] == ',')
        (*i)++;
    b = ft_atoi(line, i);
    ft_skipspace(line, i);
    if (line[*i] != '\0' || r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
    {
        all->err = 2;
        ft_error(all, "Invalid color\n");
    }    
    *color = r * 256 * 256 + g * 256 + b;
    return (0);
}

void     ft_res(t_all *all, char *line, int *i)
{
    if (all->win.x != 0 || all->win.y != 0)
    {
        all->err = 2;
        ft_error(all, "Resolution specified twice\n");
    }
    (*i)++;
    all->win.x = ft_atoi(line, i);
    all->win.y = ft_atoi(line, i);
//    if (all->win.x > 2560)
//        all->win.x = 2560;
 //   if (all->win.y > 1400)
//        all->win.y = 1400;
    if (all->win.x <= 0 || all->win.y <= 0 || line[*i] != '\0')
    {
        all->err = 2;
        ft_error(all, "Invalid resolution\n");
    }
}

int     ft_texture(t_all *all, char **tex, char *line, int *i)
{
    char *texture_file;
    int j;
    
    if (*tex != NULL)
    {
        ft_error(all, "Texture specified twice\n");
        return (2);
    }
    (*i) += 2;
    ft_skipspace(line, i);
    j = (*i);
    while(line[*i] != ' ' && line[*i] != '\0')
        (*i)++;
    if(!(texture_file = malloc(sizeof(char) * (*i - j +1))))
        return (-8);
    *i = j;
    j = 0;
    while (line[*i] != ' ' && line[*i] != '\0')
        texture_file[j++] = line[(*i)++];
    texture_file[j] = '\0';
    if (ft_name_check(texture_file, "xpm") == 0 || line[*i] != '\0')
    {
        ft_error(all, "Invalid texture\n");
        return (2);
    }
    *tex = ft_strdup(texture_file);
    free(texture_file);
    return (0);
}