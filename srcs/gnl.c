/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:10:44 by fcavillo          #+#    #+#             */
/*   Updated: 2021/04/16 15:38:20 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		ft_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ft_copy(char **line, char **buffer)
{
	int		i;
	char	*tmp;
	char	*line_tmp;

	if ((i = ft_check(*buffer)) >= 0)
	{
		tmp = ft_substr(*buffer, 0, i);
		line_tmp = *line;
		*line = ft_strjoin(*line, tmp);
		free(line_tmp);
		free(tmp);
		*buffer = ft_subbuff(*buffer, i + 1, (ft_strlen(*buffer) - i));
		return (0);
	}
	else
	{
		tmp = NULL;
		if (*line)
			tmp = *line;
		*line = ft_strjoin(*line, *buffer);
		if (tmp)
			free(tmp);
		return (1);
	}
	return (-1);
}

int		ft_eof(int ret, char **buffer, char **line)
{
	if (ret == -1)
		return (-1);
	free(*buffer);
	*buffer = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}

int		ft_free_buffer(char **buffer, t_all *all)
{
	if (all->err >= 2 && *buffer)
	{
		free(*buffer);
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line, t_all *all)
{
	static char	*buffer = NULL;
	int			ret;

	ret = 1;
	if (ft_free_buffer(&buffer, all) == 1)
		return (0);
	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	if (buffer)
		ret = ft_copy(line, &buffer);
	if (ret == 0)
		return (1);
	if (!buffer)
		if (!(buffer = malloc(sizeof(char) * BUFFER_SIZE + 1)))
			return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (!ft_copy(line, &buffer))
			return (1);
	}
	if (ret <= 0)
		return (ft_eof(ret, &buffer, line));
	return (1);
}
