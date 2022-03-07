/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:59:27 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 09:59:27 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

void	ft_destroy_img(t_data *data)
{
	mlx_destroy_image(data->mlx, data->player->img_b->mlx_img);
	mlx_destroy_image(data->mlx, data->player->img_r->mlx_img);
	mlx_destroy_image(data->mlx, data->player->img_l->mlx_img);
	mlx_destroy_image(data->mlx, data->player->img_f->mlx_img);
	mlx_destroy_image(data->mlx, data->enemy->img_b->mlx_img);
	mlx_destroy_image(data->mlx, data->enemy->img_f->mlx_img);
	mlx_destroy_image(data->mlx, data->assets->collec->mlx_img);
	mlx_destroy_image(data->mlx, data->assets->collec2->mlx_img);
	mlx_destroy_image(data->mlx, data->assets->collec3->mlx_img);
	mlx_destroy_image(data->mlx, data->assets->wall->mlx_img);
	mlx_destroy_image(data->mlx, data->assets->floor->mlx_img);
	mlx_destroy_image(data->mlx, data->assets->exit->mlx_img);
	mlx_destroy_image(data->mlx, data->img->mlx_img);
}

void	ft_free_player_assets(t_data *data)
{
	free(data->player->img_b);
	free(data->player->img_l);
	free(data->player->img_r);
	free(data->player->img_f);
	free(data->assets->wall);
	free(data->assets->collec);
	free(data->assets->collec2);
	free(data->assets->collec3);
	free(data->assets->exit);
	free(data->assets->floor);
	free(data->enemy->img_b);
	free(data->enemy->img_f);
	free(data->enemy);
	free(data->assets);
	free(data->player);
}

int	ft_free_mlx(t_data *data)
{
	ft_destroy_img(data);
	ft_free_player_assets(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->img);
	ft_free_map(data->map->map);
	free(data->map);
	free(data);
	return (0);
}
