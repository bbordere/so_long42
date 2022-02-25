/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/25 13:01:42 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



t_img		*ft_init_img(void *mlx, char *path, int width, int height)
{
	t_img	*img;
	int		size;

	size = SPRITE_SIZE;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	if (path)
		img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size,  &size);
	else
		img->mlx_img = mlx_new_image(mlx, SPRITE_SIZE * width, SPRITE_SIZE * height);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
	return (img);
}

t_assets    *ft_init_assets(void *mlx)
{
	t_assets    *asset;

	asset = malloc(sizeof(t_assets));
	if (!asset)
		return (NULL);
	asset->wall = ft_init_img(mlx, "assets/wall_2.xpm", 0, 0);
	asset->floor = ft_init_img(mlx, "assets/floor.xpm", 0, 0);
	asset->collec = ft_init_img(mlx, "assets/potion.xpm", 0, 0);
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
	player->move = 0;
	return (player);
}

t_data	*ft_init_data(char *path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->map = ft_init_map(path);
	if (ft_check_map_char(data->map) == -1)
	{
		free(data);
		exit(1);
	}
	data->mlx = mlx_init();
	data->sprite_size = SPRITE_SIZE;
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
	while (++y1 < SPRITE_SIZE)
	{
		x1 = -1;
		while (++x1 < SPRITE_SIZE)
		{
			color = ft_get_pixel(element, x1, y1);
			if (!(color == (unsigned int)(0xFF << 24)))
				my_mlx_pixel_put(mlx_img, (x * SPRITE_SIZE) + x1, (y * SPRITE_SIZE) + y1, color);
		}
	}	
}

void	ft_print_steps(t_data *data)
{
	char *str;

	str = ft_strjoin(ft_itoa(data->player->move), " steps");
	mlx_string_put(data->mlx, data->win, 0, 10, 0xFFFFFF, str);
	free(str);
}

void	ft_print_collec(t_data *data)
{
	char	*str;
	char	*col;
	char	*item;

	col = ft_itoa(data->player->nb_col);
	item = ft_itoa(data->map->item);
	str = ft_strjoin(col, " / ");
	str = ft_strjoin(str, item);
	str = ft_strjoin(str, " collectibles");
	mlx_string_put(data->mlx, data->win, 0, 25, 0xFFFFFF, str);
	// mlx_string_put(data->mlx, data->win, 0, 25, 0xFF0000 + (data->player->nb_col % data->map->item) * 5, str);
	// mlx_string_put(data->mlx, data->win, data->player->x - 35 + data->player->x * SPRITE_SIZE, 
	// 				data->player->y + data->player->y * SPRITE_SIZE - 15, 0x7FF408, str);
	free(str);
	free(item);
}

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
	ft_print_steps(data);
	ft_print_collec(data);
}

void	ft_move(int *comp, int set, t_player *player)
{
	*comp += set;
	player->move +=1;
	ft_printf("%d\n", player->move);
}

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
	mlx_destroy_image(data->mlx, data->assets->collec->mlx_img);
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
	free(data->assets->exit);
	free(data->assets->floor);
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

void	ft_on_exit(t_data *data)
{
	ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
	if (data->player->nb_col == data->map->item)
	{
		mlx_loop_end(data->mlx);
		ft_printf("YOU WIN WITH %d MOVES !\n", data->player->move);
		ft_free_mlx(data);
		exit(0);
	}
	else
		ft_printf("YOU MUST COLLECT ALL ITEMS !\n");
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
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		else
		{
			if (data->map->map[data->player->y - 1][data->player->x] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x, data->player->y - 1);
			data->map->map[data->player->y][data->player->x] = 0;
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->y, -1, data->player);
	}
	ft_paint(data->player->img_b, data->img, data->player->x, data->player->y);
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
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		else
		{
			if (data->map->map[data->player->y + 1][data->player->x] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x,  data->player->y + 1);
			data->map->map[data->player->y][data->player->x] = 0;
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->y, 1, data->player);
	}
	ft_paint(data->player->img_f, data->img, data->player->x, data->player->y);
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
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		else
		{
			if (data->map->map[data->player->y][data->player->x - 1] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x - 1, data->player->y);
			data->map->map[data->player->y][data->player->x] = 0;
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->x, -1, data->player);
	}
	ft_paint(data->player->img_l, data->img, data->player->x, data->player->y);
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
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		else
		{
			if (data->map->map[data->player->y][data->player->x + 1] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x + 1, data->player->y);
			data->map->map[data->player->y][data->player->x] = 0;
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->x, 1, data->player);
	}
	ft_paint(data->player->img_r, data->img, data->player->x, data->player->y);
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}

int	ft_quit(t_data *data)
{
	mlx_loop_end(data->mlx);
	ft_free_mlx(data);
	exit(0);
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == 'd' || keycode == 65363)
		// ft_check_pos(data, RIGHT);
		ft_right(data);
	else if (keycode == 'a' || keycode == 65361)
		// ft_check_pos(data, LEFT);
		ft_left(data);
	else if (keycode == 'w' || keycode == 65362)
		// ft_check_pos(data, UP);
		ft_up(data);
	else if (keycode == 's'|| keycode == 65364)
		// ft_check_pos(data, DOWN);
		ft_down(data);
	else if (keycode == 65307)
		ft_quit(data);
	ft_print_steps(data);
	ft_print_collec(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data 	*data;
	
	(void)ac;
	data = ft_init_data(av[1]);
	ft_render_map(data);
	mlx_hook(data->win, 2, (1L << 0), ft_key_hook, data);
	mlx_hook(data->win, 17, (1L << 0), ft_quit, data);
	// mlx_loop_hook(data->mlx, ft_key_hook, data);
	mlx_loop(data->mlx);

}