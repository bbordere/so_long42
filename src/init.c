/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:33:35 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/06 20:33:35 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	*ft_init_img(void *mlx, char *path, int width, int height)
{
	t_img	*img;
	int		size;

	size = SPRITE_SIZE;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	if (path)
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size, &size);
	else
		img->mlx_img = mlx_new_image(mlx, SPRITE_SIZE * width,
				SPRITE_SIZE * height);
	if (!img->mlx_img)
		return (ft_free(img));
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		return (NULL);
	return (img);
}

t_assets	*ft_init_assets(void *mlx)
{
	t_assets	*asset;

	asset = malloc(sizeof(t_assets));
	if (!asset)
		return (NULL);
	asset->wall = ft_init_img(mlx, "assets/wall_2.xpm", 0, 0);
	asset->floor = ft_init_img(mlx, "assets/floor.xpm", 0, 0);
	asset->collec = ft_init_img(mlx, "assets/potion.xpm", 0, 0);
	asset->exit = ft_init_img(mlx, "assets/exit.xpm", 0, 0);
	if (!asset->collec || !asset->exit || !asset->wall || !asset->floor)
		return (ft_free_assets(asset, mlx));
	return (asset);
}

t_player	*ft_init_player(void *mlx)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->img_b = ft_init_img(mlx, "assets/player_B.xpm", 0, 0);
	player->img_f = ft_init_img(mlx, "assets/player_F.xpm", 0, 0);
	player->img_l = ft_init_img(mlx, "assets/player_L.xpm", 0, 0);
	player->img_r = ft_init_img(mlx, "assets/player_R.xpm", 0, 0);
	player->on_exit = 0;
	player->nb_col = 0;
	player->dir = 0;
	player->move = 0;
	if (!player->img_b || !player->img_f || !player->img_l
		|| !player->img_r)
		return (ft_free_player(player, mlx));
	return (player);
}

t_data	*ft_init_data(char *path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->map = ft_init_map(path);
	if (!data->map)
		ft_error_exit_msg(data->map, data, "/!\\ Error\nInitialization map !\n");
	if (ft_check_map_char(data->map) == -1)
		ft_error_exit_msg(data, NULL, "");
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_free_map_data(data));
	data->sprite_size = SPRITE_SIZE;
	data->assets = ft_init_assets(data->mlx);
	data->img = ft_init_img(data->mlx, NULL,
			data->map->width, data->map->height);
	data->player = ft_init_player(data->mlx);
	data->win = mlx_new_window(data->mlx, data->map->width * data->sprite_size,
			data->map->height * data->sprite_size, "so_long");
	if (!data->map || !data->assets || !data->img || !data->player
		|| !data->win)
		return (ft_free_data(data));
	return (data);
}
