/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/22 14:18:23 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



t_img		*ft_init_img(void *mlx, char *path, int width, int height)
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
		img->mlx_img = mlx_new_image(mlx, 64 * width, 64 * height);
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
	asset->wall = ft_init_img(mlx, "assets/wall_2.xpm", 0, 0);
	asset->floor = ft_init_img(mlx, "assets/clay.xpm", 0, 0);
	asset->collec = ft_init_img(mlx, "assets/amethyst.xpm", 0, 0);
	asset->exit = ft_init_img(mlx, "assets/wall.xpm", 0, 0);
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
	player->img_b = ft_init_img(mlx, "assets/player_B.xpm", 0, 0);
	player->img_f = ft_init_img(mlx, "assets/player_F.xpm", 0, 0);
	player->img_l = ft_init_img(mlx, "assets/player_L.xpm", 0, 0);
	player->img_r = ft_init_img(mlx, "assets/player_R.xpm", 0, 0);
	player->on_exit = 0;
	player->nb_col = 0;
	player->dir = 0;
	player->moove = 0;
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
	data->img = ft_init_img(data->mlx, NULL, data->map->width, data->map->height);
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

void	ft_paint(t_img *element, t_img *mlx_img, int x, int y)
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
			color = ft_get_pixel(element, x1, y1);
			if (!(color == (unsigned int)(0xFF << 24)))
				my_mlx_pixel_put(mlx_img, (x * 64) + x1, (y * 64) + y1, color);
		}
	}	
}

void	ft_check_item(t_data *data)
{
	if (data->map->map[data->player->y][data->player->x] == 'C')
	{
		data->map->map[data->player->y][data->player->x] = '0';
		data->player->nb_col += 1;
	}
	if (data->map->map[data->player->y][data->player->x] == 'E')
	{
		if (data->player->nb_col == data->map->item)
		{
			mlx_loop_end(data->mlx);
			ft_putstr_fd("YOU WIN !\n",1);
			exit(0);
		}
		else if (data->player->on_exit == 0)
		{
			ft_putstr_fd("YOU MUST COLLECT ALL ITEMS !\n",1);
			data->player->on_exit = 1;
		}
	}
	else
		data->player->on_exit = 0;
}

void	ft_move(int *comp, int set, t_player *player)
{
	*comp += set;
	player->moove +=1;
	printf("%d\n", player->moove);
}

void	ft_check_pos(t_data *data, int dir)
{
	if (dir == RIGHT)
	{
		if (!(data->map->map[data->player->y][data->player->x + 1] == '1'))
			ft_move(&data->player->x, 1, data->player);
		data->player->dir = RIGHT;
	}
	else if (dir == LEFT)
	{
		if (!(data->map->map[data->player->y][data->player->x - 1] == '1'))
			ft_move(&data->player->x, -1, data->player);
		data->player->dir = LEFT;
	}
	else if (dir == UP)
	{
		if (!(data->map->map[data->player->y - 1][data->player->x] == '1'))
			ft_move(&data->player->y, -1, data->player);
		data->player->dir = UP;
	}
	else if (dir == DOWN)
	{
		if (!(data->map->map[data->player->y + 1][data->player->x] == '1'))
			ft_move(&data->player->y, 1, data->player);
		data->player->dir = DOWN;
	}
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == 'd' || keycode == 65363)
		ft_check_pos(data, RIGHT);
	else if (keycode == 'a' || keycode == 65361)
		ft_check_pos(data, LEFT);
	else if (keycode == 'w' || keycode == 65362)
		ft_check_pos(data, UP);
	else if (keycode == 's'|| keycode == 65364)
		ft_check_pos(data, DOWN);
	else if (keycode == 65307)
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

void	ft_render_player(t_data *data)
{
	if (data->player->dir == RIGHT)
		ft_paint(data->player->img_r, data->img, data->player->x, data->player->y);
	if (data->player->dir == LEFT)
		ft_paint(data->player->img_l, data->img, data->player->x, data->player->y);
	if (data->player->dir == UP)
		ft_paint(data->player->img_b, data->img, data->player->x, data->player->y);
	if (data->player->dir == DOWN)
		ft_paint(data->player->img_f, data->img, data->player->x, data->player->y);
	if (data->player->dir == 0)
		ft_paint(data->player->img_f, data->img, data->player->x, data->player->y);
}

int	ft_render_map(t_data *data)
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
			{
				data->player->x = x;
				data->player->y = y;
				data->map->map[y][x] = '0';
			}
		}		
	}
	ft_check_item(data);
	ft_render_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data 	*data;
	
	
	data = ft_init_data(av[1]);
	// mlx_key_hook(data->win, ft_key_hook, data);
	mlx_hook(data->win, 2, 1L, ft_key_hook, data);
	mlx_hook(data->win, 17, 1L, mlx_loop_end, data->mlx);
	mlx_loop_hook(data->mlx, ft_render_map, data);
	mlx_loop(data->mlx);

}