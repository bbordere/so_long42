/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:43:58 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 09:43:58 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_enemy(t_data *data, int dir)
{
	if (dir == LEFT)
		if (data->map->map[data->player->y][data->player->x - 1] == 'S')
			ft_quit_msg(data, "GAME OVER !");
	if (dir == RIGHT)
		if (data->map->map[data->player->y][data->player->x + 1] == 'S')
			ft_quit_msg(data, "GAME OVER !");
	if (dir == UP)
		if (data->map->map[data->player->y - 1][data->player->x] == 'S')
			ft_quit_msg(data, "GAME OVER !");
	if (dir == DOWN)
		if (data->map->map[data->player->y + 1][data->player->x] == 'S')
			ft_quit_msg(data, "GAME OVER !");
}

void	ft_up(t_data *data)
{
	ft_check_enemy(data, UP);
	if (data->map->map[data->player->y - 1][data->player->x] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y - 1][data->player->x] == 'E')
		ft_on_exit(data);
	if (!(data->map->map[data->player->y - 1][data->player->x] == '1'))
		ft_paint_up(data);
	ft_paint(data->player->img_b, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

void	ft_down(t_data *data)
{
	ft_check_enemy(data, DOWN);
	if (data->map->map[data->player->y + 1][data->player->x] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y + 1][data->player->x] == 'E')
		ft_on_exit(data);
	if (!(data->map->map[data->player->y + 1][data->player->x] == '1'))
		ft_paint_down(data);
	ft_paint(data->player->img_f, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

void	ft_left(t_data *data)
{
	ft_check_enemy(data, LEFT);
	if (data->map->map[data->player->y][data->player->x - 1] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y][data->player->x - 1] == 'E')
		ft_on_exit(data);
	if (!(data->map->map[data->player->y][data->player->x - 1] == '1'))
		ft_paint_left(data);
	ft_paint(data->player->img_l, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

void	ft_right(t_data *data)
{
	ft_check_enemy(data, RIGHT);
	if (data->map->map[data->player->y][data->player->x + 1] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y][data->player->x + 1] == 'E')
		ft_on_exit(data);
	if (!(data->map->map[data->player->y][data->player->x + 1] == '1'))
		ft_paint_right(data);
	ft_paint(data->player->img_r, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}
