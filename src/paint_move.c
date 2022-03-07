/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:10:55 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 09:10:55 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_paint_up(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x] == 'E')
	{
		ft_paint(data->assets->floor, data->img, data->player->x,
			data->player->y);
		ft_paint(data->assets->exit, data->img, data->player->x,
			data->player->y);
	}
	else
	{
		if (data->map->map[data->player->y - 1][data->player->x] == 'C')
			ft_paint(data->assets->floor, data->img,
				data->player->x, data->player->y - 1);
		data->map->map[data->player->y][data->player->x] = '0';
		ft_paint(data->assets->floor, data->img,
			data->player->x, data->player->y);
	}
	ft_move(&data->player->y, -1, data->player);
}

void	ft_paint_down(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x] == 'E')
	{
		ft_paint(data->assets->floor, data->img, data->player->x,
			data->player->y);
		ft_paint(data->assets->exit, data->img, data->player->x,
			data->player->y);
	}
	else
	{
		if (data->map->map[data->player->y + 1][data->player->x] == 'C')
			ft_paint(data->assets->floor, data->img, data->player->x,
				data->player->y + 1);
		data->map->map[data->player->y][data->player->x] = '0';
		ft_paint(data->assets->floor, data->img, data->player->x,
			data->player->y);
	}
	ft_move(&data->player->y, 1, data->player);
}

void	ft_paint_left(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x] == 'E')
	{
		ft_paint(data->assets->floor, data->img, data->player->x,
			data->player->y);
		ft_paint(data->assets->exit, data->img, data->player->x,
			data->player->y);
	}
	else
	{
		if (data->map->map[data->player->y][data->player->x - 1] == 'C')
			ft_paint(data->assets->floor, data->img, data->player->x - 1,
				data->player->y);
		data->map->map[data->player->y][data->player->x] = '0';
		ft_paint(data->assets->floor, data->img, data->player->x,
			data->player->y);
	}
	ft_move(&data->player->x, -1, data->player);
}

void	ft_paint_right(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x] == 'E')
	{
		ft_paint(data->assets->floor, data->img, data->player->x,
			data->player->y);
		ft_paint(data->assets->exit, data->img, data->player->x,
			data->player->y);
	}
	else
	{
		if (data->map->map[data->player->y][data->player->x + 1] == 'C')
			ft_paint(data->assets->floor, data->img, data->player->x + 1,
				data->player->y);
		data->map->map[data->player->y][data->player->x] = '0';
		ft_paint(data->assets->floor, data->img, data->player->x,
			data->player->y);
	}
	ft_move(&data->player->x, 1, data->player);
}
