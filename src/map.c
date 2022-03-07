/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:36:37 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/06 20:36:37 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_fill_map(t_map *o_map)
{
	char	**map;
	char	*str;
	char	*line;

	str = NULL;
	line = get_next_line(o_map->fd_map);
	if (!line)
		return (NULL);
	o_map->width = ft_strlen(line) - 1;
	o_map->height = 0;
	while (line)
	{
		o_map->height++;
		str = ft_strjoin(str, line);
		if (!str)
			return (NULL);
		free(line);
		line = get_next_line(o_map->fd_map);
	}
	map = ft_split(str, '\n');
	if (!map)
		return (ft_free(str));
	free(str);
	return (map);
}

t_map	*ft_init_map(char *file)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->fd_map = open(file, O_RDONLY);
	if (map->fd_map == -1)
		return (ft_free(map));
	map->x = 0;
	map->y = 0;
	map->item = 0;
	map->start = 0;
	map->exit = 0;
	map->map = ft_fill_map(map);
	if (!map->map)
		return (ft_free(map));
	return (map);
}
