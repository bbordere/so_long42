/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/20 14:28:40 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



t_img		*ft_init_img(void *mlx, char *path)
{
	t_img	*img;
	int		size;

	size = 64;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	if (path)
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size,  &size);
	else
		img->mlx_img = mlx_new_image(mlx, 64 * 26, 64 * 13);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
	return (img);
}

t_assets    *ft_init_assets(void *mlx)
{
	t_assets    *asset;
	int 		size;

	asset = malloc(sizeof(t_assets));
	if (!asset)
		return (NULL);
	size = 64;
	asset->wall = ft_init_img(mlx, "assets/wall_2.xpm");
	asset->floor = ft_init_img(mlx, "assets/clay.xpm");
	asset->collec = ft_init_img(mlx, "assets/amethyst.xpm");
	asset->tmp = mlx_new_image(mlx, size, size);
	return (asset);
}

char	**ft_fill_map(t_map *o_map)
{
	char	**map;
	char	*str;
	char	*line;

	str = NULL;
	line = get_next_line(o_map->fd_map);
	if (!line)
		return (NULL);
	o_map->width = ft_strlen(line) - 1;
	o_map->height = 0;
	while (line)
	{
		o_map->height++;
		str = ft_strjoin(str, line);
		if (!str)
			return (NULL);
			//error free all
		free(line);
		line = get_next_line(o_map->fd_map);
	}
	map = ft_split(str, '\n');
	if (!map)
		return (NULL);
		//error free all
	free(str);
	return (map);
}

t_map	*ft_init_map(char *file)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->fd_map = open(file, O_RDONLY);
	if (map->fd_map == -1)
		return (NULL);
	map->x = 0;
	map->y = 0;
	map->item = 0;
	map->start = 0;
	map->exit = 0;
	map->map = ft_fill_map(map);
	return (map);
}

t_player	*ft_init_player(void *mlx)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->img_b = ft_init_img(mlx, "assets/player_B.xpm");
	player->img_f = ft_init_img(mlx, "assets/player_F.xpm");
	player->img_l = ft_init_img(mlx, "assets/player_L.xpm");
	player->img_r = ft_init_img(mlx, "assets/player_R.xpm");
	player->nb_col = 0;
	return (player);
}

t_data	*ft_init_data(char *path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->sprite_size = 64;	
	data->mlx = mlx_init();
	data->map = ft_init_map(path);
	ft_check_map_char(data->map);
	data->assets = ft_init_assets(data->mlx);
	data->img = ft_init_img(data->mlx, NULL);
	data->player = ft_init_player(data->mlx);
	data->win = mlx_new_window(data->mlx, data->map->width * data->sprite_size, 
							data->map->height * data->sprite_size, "so_long");
	return (data);

}

unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	unsigned int	color;
	char			*pix;

	pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pix;
	return (color);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ft_paint(t_img *ground, t_img *mlx_img, int x, int y)
{
	int				x1;
	int				y1;
	unsigned int	color;

	y1 = -1;
	while (++y1 < 64)
	{
		x1 = -1;
		while (++x1 < 64)
		{
			color = ft_get_pixel(ground, x1, y1);
			if (!(color == (unsigned int)(0xFF << 24)))
				my_mlx_pixel_put(mlx_img, (x * 64) + x1, (y * 64) + y1, color);
		}
	}
	
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == 'd')
		ft_putstr_fd("Hello\n", 1);
	if (keycode == 65307)
	{
		mlx_loop_end(data->mlx);
		exit(0);
	}
	return (0);
}

void	ft_destroy_imgs(t_data *data)
{
	mlx_destroy_image(data->mlx, data->assets->floor->mlx_img);
}

int	main(void)
{
	t_data 	*data;
	int		x;
	int		y;
	
	data = ft_init_data("map/map.ber");
	// y = 0;
	// while (y < data->map->height)
	// {
	// 	x = 0;
	// 	data->map->x = 0;
	// 	while (x < data->map->width)
	// 	{
	// 		if (data->map->map[y][x] == '1')
	// 			mlx_put_image_to_window(data->mlx, data->win, data->assets->wall->mlx_img, data->map->x, data->map->y);
	// 		else if (data->map->map[y][x] == 'C')
	// 			mlx_put_image_to_window(data->mlx, data->win, data->assets->collec->mlx_img, data->map->x, data->map->y);
	// 		else
	// 			mlx_put_image_to_window(data->mlx, data->win, data->assets->floor->mlx_img, data->map->x, data->map->y);
	// 		data->map->x += data->sprite_size;
	// 		x++;
	// 	}
	// 	data->map->y += data->sprite_size;
	// 	y++;
	// }
	// t_img *img;
	// img = ft_init_img(data->mlx, NULL);
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
			if (data->map->map[y][x] == 'P')
			{
				data->player->x = x;
				data->player->y = y;
				ft_paint(data->player->img_f, data->img, x, y);
			}
		}		
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
	mlx_key_hook(data->win, ft_key_hook, &data);
	mlx_loop(data->mlx);
	ft_destroy_imgs(data);

}