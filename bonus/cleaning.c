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

void	*ft_free_player(t_player *player, void *mlx)
{
	if (player->img_b)
		mlx_destroy_image(mlx, player->img_b->mlx_img);
	if (player->img_f)
		mlx_destroy_image(mlx, player->img_f->mlx_img);
	if (player->img_l)
		mlx_destroy_image(mlx, player->img_l->mlx_img);
	if (player->img_r)
		mlx_destroy_image(mlx, player->img_r->mlx_img);
	free(player->img_b);
	free(player->img_l);
	free(player->img_r);
	free(player->img_f);
	free(player);
	return (NULL);
}

void	*ft_free_assets(t_assets *assets, void *mlx)
{
	if (assets->collec)
		mlx_destroy_image(mlx, assets->collec->mlx_img);
	if (assets->collec2)
		mlx_destroy_image(mlx, assets->collec2->mlx_img);
	if (assets->collec3)
		mlx_destroy_image(mlx, assets->collec3->mlx_img);
	if (assets->wall)
		mlx_destroy_image(mlx, assets->wall->mlx_img);
	if (assets->exit)
		mlx_destroy_image(mlx, assets->exit->mlx_img);
	if (assets->floor)
		mlx_destroy_image(mlx, assets->floor->mlx_img);
	free(assets->wall);
	free(assets->collec);
	free(assets->collec2);
	free(assets->collec3);
	free(assets->floor);
	free(assets->exit);
	free(assets);
	return (NULL);
}

void	*ft_free_enemy(t_enemy *enemy, void *mlx)
{
	if (enemy->img_b)
		mlx_destroy_image(mlx, enemy->img_b->mlx_img);
	if (enemy->img_f)
		mlx_destroy_image(mlx, enemy->img_f->mlx_img);
	free(enemy->img_b);
	free(enemy->img_f);
	free(enemy);
	return (NULL);
}

void	*ft_free_data(t_data *data)
{
	if (data->map)
	{
		ft_free_map(data->map->map);
		close(data->map->fd_map);
		free(data->map);
	}
	if (data->assets)
		ft_free_assets(data->assets, data->mlx);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img->mlx_img);
	if (data->player)
		ft_free_player(data->player, data->mlx);
	if (data->enemy)
		ft_free_enemy(data->enemy, data->mlx);
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data->img);
	free(data);
	return (NULL);
}
