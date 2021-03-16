/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:45:56 by fcavillo          #+#    #+#             */
/*   Updated: 2021/03/16 09:11:22 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h" 

void     ft_line(t_all *all, char *line)
{
    int     i;
    
    i = 0;
    ft_skipspace(line, &i);
    if (line[i] == 'R' && line[i + 1] == ' ')
        ft_res(all, line, &i);
    else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
        all->err = ft_texture(all, &all->tex.n, line, &i);
    else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
        all->err = ft_texture(all, &all->tex.s, line, &i);
    else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
        all->err = ft_texture(all, &all->tex.w, line, &i);
    else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
        all->err = ft_texture(all, &all->tex.e, line, &i);
    else if (line[i] == 'S' && line[i + 1] == ' ')
        all->err = ft_texture(all, &all->tex.spr, line, &i);
    else if (line[i] == 'F' && line[i + 1] == ' ')
        ft_colors(all, &all->tex.f, line, &i);
    else if (line[i] == 'C' && line[i + 1] == ' ')
        ft_colors(all, &all->tex.c, line, &i);
}



void    ft_parse(char *mapname, t_all *all)
{
    int fd;
    int ret;
    char *line;
    
    ret = 1;
    line = NULL;
    if ((fd = open(mapname, O_DIRECTORY)) != -1)
        return (ft_error(all, "Argv2 is a directory\n"));
    else if ((fd = open(mapname, O_RDONLY)) == -1)
        return (ft_error(all, "Invalid .cub file\n"));
    all->err = 0;
    while (ret != 0 && all->err != 2)
    {
        ret = get_next_line(fd, &line, all);
        if (all->err == 2)
            ft_error(all, "Parsing error\n");
        ft_line(all, line); 
        ft_map(line, all);
        free(line); 
    }
    close(fd);
    if (all->map.x == 0 || all->map.y == 0 || all->err == 2)
        ft_error(all, "Missing parameter in .cub\n");
    else
        ft_map_parsing(mapname, all);
}

int     ft_start(char *str, t_all *all)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    if (i > 4 && str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c'
        && str[i - 4] == '.')
        ft_parse(str, all); 
    else
        ft_error(all, "Invalid Map Name\n");
    return (0);
    }

int     main(int ac, char **av)
{
    t_all all;

    all.save = 0;
    ft_init(&all);
    if (ac == 2 || (ac == 3 && ft_check_save(av[2]) == 1))
    {
        if (ac == 3)
            all.save = 1;
        ft_start(av[1], &all);
    }
    else
        printf("%sError\nInvalid Args\n", RED);\
    printf("%sTESTING\n", GRN);
    test(&all);
    printf("%sTHE TESTING HAS BEEN TESTED\n", GRN);
    free_all(&all);
    printf("%sThe End\n", YEL);
    return(0);
}