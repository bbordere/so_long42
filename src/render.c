/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 08:54:47 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 08:54:47 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_render_player(t_data *data, int x, int y)
{	
	data->player->x = x;
	data->player->y = y;
	data->map->map[y][x] = '0';
	ft_paint(data->player->img_f, data->img, x, y);
}

void	ft_render_map(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			ft_paint(data->assets->floor, data->img, x, y);
			if (data->map->map[y][x] == '1')
				ft_paint(data->assets->wall, data->img, x, y);
			if (data->map->map[y][x] == 'C')
				ft_paint(data->assets->collec, data->img, x, y);
			if (data->map->map[y][x] == 'E')
				ft_paint(data->assets->exit, data->img, x, y);
			if (data->map->map[y][x] == 'P')
				ft_render_player(data, x, y);
		}		
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

void	ft_on_exit(t_data *data)
{
	ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
	if (data->player->nb_col == data->map->item)
	{
		mlx_loop_end(data->mlx);
		ft_printf("YOU WIN WITH %d MOVES !\n", data->player->move);
		close(data->map->fd_map);
		ft_free_mlx(data);
		exit(0);
	}
	else
		ft_printf("YOU MUST COLLECT ALL ITEMS !\n");
}
