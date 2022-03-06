/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:33:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/06 23:33:52 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_move(int *comp, int set, t_player *player)
{
	*comp += set;
	player->move +=1;
	ft_printf("%d\n", player->move);
}

void	ft_up(t_data *data)
{
	if (data->map->map[data->player->y - 1][data->player->x] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y - 1][data->player->x] == 'E')
			ft_on_exit(data);
	if (!(data->map->map[data->player->y - 1][data->player->x] == '1'))
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y - 1][data->player->x] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x, data->player->y - 1);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->y, -1, data->player);
	}
	ft_paint(data->player->img_b, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

void	ft_down(t_data *data)
{
	if (data->map->map[data->player->y + 1][data->player->x] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y + 1][data->player->x] == 'E')
			ft_on_exit(data);
	if (!(data->map->map[data->player->y + 1][data->player->x] == '1'))
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y + 1][data->player->x] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x,  data->player->y + 1);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->y, 1, data->player);
	}
	ft_paint(data->player->img_f, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

void	ft_left(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x - 1] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y][data->player->x - 1] == 'E')
			ft_on_exit(data);
	if (!(data->map->map[data->player->y][data->player->x - 1] == '1'))
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y][data->player->x - 1] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x - 1, data->player->y);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->x, -1, data->player);
	}
	ft_paint(data->player->img_l, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

void	ft_right(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x + 1] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y][data->player->x + 1] == 'E')
			ft_on_exit(data);
	if (!(data->map->map[data->player->y][data->player->x + 1] == '1'))
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y][data->player->x + 1] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x + 1, data->player->y);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->x, 1, data->player);
	}
	ft_paint(data->player->img_r, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}