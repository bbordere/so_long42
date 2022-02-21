/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:01:39 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/21 16:04:56 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_char_in(char *str, t_map *map)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != '1' && str[i] != '0' && str[i] != 'C' 
			&& str[i] != 'E' && str[i] != 'P')
			return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == 'C')
			map->item += 1;
		// if (str[i] == 'E')
		// 	map->item += 1;
		// if (str[i] == 'P')
		// 	map->item += 1;
	}
	return (0);
}

int	ft_check_wall(t_map *map)
{
	int i;

	i = -1;
	while (map->map[0][++i])
		if (map->map[0][i] != '1')
			return (-1);
	i = 0;
	while (++i < map->height - 2)
		if (map->map[i][map->width - 1] != '1' || map->map[i][0] != '1')
			return (-1);
	i = -1;
	while (map->map[map->height - 1][++i])
		if (map->map[map->height - 1][i] != '1')
			return (-1);
	return (0);    
}

void	ft_error(void)
{
	ft_putstr_fd("Error\n", 1);
	exit(1);
}

int	ft_check_map_char(t_map *map)
{
	int i;

	i = -1;
	if (ft_check_wall(map) == -1)
		ft_error();
	while (map->map[++i])
	{
		if (ft_strlen(map->map[i]) != map->width)
			ft_error();
		if (ft_char_in(map->map[i], map) == -1)
			ft_error();        
	}
	
}