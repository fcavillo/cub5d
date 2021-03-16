/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:59:45 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/12 13:49:38 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"



int     ft_line_is_map(char *line, t_all *all)
{
    int i;

    i = 0;
    if (!line)
        return (0);
    if (ft_str_has(line, '1') == 1 || ft_str_has(line, '0') == 1)
    {
        while (line[i] != '\0')
        {
            if (line[i] != ' ' && line[i] != '0' && line[i] != '1' 
				&& line[i] != '2' && line[i] != 'N' && line[i] != 'S' 
				&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n'
				&& line[i] != '\t')
            {
				if (all->map.inmap == 1)
					all->map.charmap = 2; //whywhywhy
				return (0);                        
            }
            i++;
        }
        return (1);
    }
    return (0);
}

int     ft_map_copy(char *line, t_all *all)
{
    static int  i = 0;
    int         j;

    j = 0;
    all->map.cub[i] = NULL;
    if(!(all->map.cub[i] = malloc(sizeof(char) * (all->map.x + 1)))) // added parenthesis
        return (0);
    while (line[j]) //copie line dans map
    {
        if (ft_spawn_and_sprite(line[j], all, i, j) == 1)
            all->map.cub[i][j] = '0';
        else if (line[j] == ' ')
            all->map.cub[i][j] = ' '; //remplacer par des 1?
        else
            all->map.cub[i][j] = line[j];
        j++;
    }
    while (j <= all->map.x - 1) //tester avec strict et pas de -1 / completait ave des 0
    {
        all->map.cub[i][j] = ' ';
        j++;
    }
    all->map.cub[i][j] = '\0';
    i++;    
    return (0);
}

void     ft_copied_map_parsing(t_all *all)
{
    int i;

    i = 0;
    ft_check_map(all);     
    ft_load_sprite(all);
    ft_check_errors(all);
    ft_ray(all);
}

int     ft_map_parsing(char *mapname, t_all *all)
{
    int     fd;
    int     ret;
    char     *line;

    ret = 1;
    line = NULL;
    fd = open(mapname, O_RDONLY);
    if (!(all->map.cub = (char **)malloc(sizeof(char *) * all->map.y)))
        return (0);
    while (ret != 0)
    {
        ret = get_next_line(fd, &line, all);
        if (all->map.inmap == 1 && ft_empty_line(line) 
                && all->map.count < all->map.y)
            all->map.emptyline = 1; //whywhywhy
        if ((all->map.inmap = ft_line_is_map(line, all)) == 1)
        {
            all->map.count = all->map.count + 1;
            ft_map_copy(line, all);
        }
        free(line);
    }
    close(fd);
    ft_copied_map_parsing(all);
    return (0);
}

void    ft_map(char *line, t_all *all)
{
    int         i;
    static int  nbline = 0;
    static int  sizeline = 0;

    i = 0;
    if (ft_line_is_map(line, all) == 1)
    {
        if (all->tex.c == -1 || all->tex.f == -1 || all->tex.n == NULL ||
              all->tex.w == NULL || all->tex.e == NULL ||
              all->tex.s == NULL || all->tex.spr == NULL)
            all->err = 2;
        if (ft_strlen(line) > sizeline)
            sizeline = ft_strlen(line);
        nbline = nbline + 1;
    }
    all->map.x = sizeline;
    all->map.y = nbline;
}