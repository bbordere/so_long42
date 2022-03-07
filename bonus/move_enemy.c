/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:50:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 09:50:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_move_up_enemy(t_data *data, int x, int y)
{
	if (data->map->map[y - 1][x] == 'C')
	{
		data->enemy->on_wall = 0;
		return ;
	}
	if (data->map->map[y - 1][x] == 'P')
		ft_quit_msg(data, "GAME OVER !");
	data->map->map[y][x] = '0';
	ft_paint(data->assets->floor, data->img, x, y);
	data->map->map[y - 1][x] = 'S';
	ft_paint(data->enemy->img_b, data->img, x, y - 1);
	if (data->map->map[y - 2][x] == '1')
		data->enemy->on_wall = 0;
}

void	ft_move_down_enemy(t_data *data, int x, int y)
{
	if (data->map->map[y + 1][x] == 'C' || data->map->map[y + 1][x] == 'S')
	{
		data->enemy->on_wall = 1;
		return ;
	}
	if (data->map->map[y + 1][x] == 'P')
		ft_quit_msg(data, "GAME OVER !");
	data->map->map[y][x] = '0';
	ft_paint(data->assets->floor, data->img, x, y);
	data->map->map[y + 1][x] = 'S';
	ft_paint(data->enemy->img_f, data->img, x, y + 1);
	if (data->map->map[y + 2][x] == '1')
		data->enemy->on_wall = 1;
}

void	ft_do_move_enemy(t_data *data, int x, int y, int dir)
{
	if (dir == DOWN)
		ft_move_down_enemy(data, x, y);
	else if (dir == UP)
		ft_move_up_enemy(data, x, y);
}
