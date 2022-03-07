/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:26:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 09:26:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_free_data(t_data *data)
{
	if (data->map)
	{
		ft_free_map(data->map->map);
		free(data->map);
	}
	if (data->assets)
		ft_free_assets(data->assets, data->mlx);
	if (data->img)
		ft_free_img(data->img, data->mlx);
	if (data->player)
		ft_free(data->player);
	if (data->enemy)
		ft_free_enemy(data->enemy, data->mlx);
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		free(data->win);
	}
	free(data->mlx);
	return (NULL);
}

void	*ft_free_player(t_player *player, void *mlx)
{
	if (player->img_b)
		ft_free_img(player->img_b, mlx);
	if (player->img_f)
		ft_free_img(player->img_b, mlx);
	if (player->img_l)
		ft_free_img(player->img_b, mlx);
	if (player->img_r)
		ft_free_img(player->img_b, mlx);
	free(player);
	return (NULL);
}

void	*ft_free_img(t_img	*img, void *mlx)
{
	if (img->addr)
		free(img->addr);
	if (img->mlx_img)
		mlx_destroy_image(mlx, img->mlx_img);
	free(img);
	return (NULL);
}

void	*ft_free_assets(t_assets *assets, void *mlx)
{
	if (assets->collec2)
		ft_free_img(assets->collec2, mlx);
	if (assets->collec)
		ft_free_img(assets->collec, mlx);
	if (assets->collec3)
		ft_free_img(assets->collec3, mlx);
	if (assets->wall)
		ft_free_img(assets->wall, mlx);
	if (assets->exit)
		ft_free_img(assets->exit, mlx);
	if (assets->floor)
		ft_free_img(assets->floor, mlx);
	free(assets);
	return (NULL);
}

void	*ft_free_enemy(t_enemy *enemy, void *mlx)
{
	if (enemy->img_b)
		ft_free_img(enemy->img_b, mlx);
	if (enemy->img_f)
		ft_free_img(enemy->img_f, mlx);
	free(enemy);
	return (NULL);
}
