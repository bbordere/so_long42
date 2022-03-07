/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:57:35 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 09:57:35 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_anim_enemy(t_data *data, int x, int y)
{
	if ((data->map->map[y - 1][x] == 'P' && data->enemy->dir == UP)
		|| (data->map->map[y][x] == 'P' && data->enemy->dir == DOWN))
		ft_quit_msg(data, "GAME OVER !");
	if (data->e_tick == 300)
	{	
		if (data->map->map[y + 1][x] != '1' && data->enemy->on_wall == 0)
		{
			ft_do_move_enemy(data, x, y, DOWN);
			data->enemy->dir = DOWN;
		}
		else if (data->map->map[y - 1][x] != '1' && data->enemy->on_wall == 1)
		{
			ft_do_move_enemy(data, x, y, UP);
			data->enemy->dir = UP;
		}
		else
			data->enemy->on_wall = 1;
		data->e_tick = 0;
	}
	data->e_tick += 1;
}

void	ft_anim_pot(t_data *data, int x, int y)
{
	if (data->c_tick == 1)
	{
		ft_paint(data->assets->floor, data->img, x, y);
		ft_paint(data->assets->collec, data->img, x, y);
	}
	if (data->c_tick == 200)
		ft_paint(data->assets->collec2, data->img, x, y);
	if (data->c_tick == 300)
		ft_paint(data->assets->collec3, data->img, x, y);
	if (data->c_tick == 400)
	{
		ft_paint(data->assets->collec2, data->img, x, y);
	}
	if (data->c_tick == 500)
		data->c_tick = 0;
}

void	ft_do_anim(t_data *data)
{
	int	x;
	int	y;

	data->c_tick += 1;
	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			if (data->map->map[y][x] == 'C')
				ft_anim_pot(data, x, y);
			else if (data->map->map[y][x] == 'S')
				ft_anim_enemy(data, x, y);
		}		
	}
}

int	ft_animations(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x] == 'C')
		data->map->map[data->player->y][data->player->x] = '0';
	ft_do_anim(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->img->mlx_img, 0, 0);
	ft_print_steps(data);
	ft_print_collec(data);
	return (0);
}
