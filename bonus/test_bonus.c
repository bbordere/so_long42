/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/28 16:28:24 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void		*ft_free_img(t_img	*img, void *mlx)
{
	if (img->addr)
		free(img->addr);
	if (img->mlx_img)
		mlx_destroy_image(mlx, img->mlx_img);
	free(img);
	return (NULL);
}

void		*ft_free_assets(t_assets *assets, void *mlx)
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
	if (!img->addr || !img->mlx_img)
		return (ft_free_img(img, mlx));
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
	asset->collec2 = ft_init_img(mlx, "assets/potion2.xpm", 0, 0);
	asset->collec3 = ft_init_img(mlx, "assets/potion3.xpm", 0, 0);
	asset->exit = ft_init_img(mlx, "assets/exit.xpm", 0, 0);
	if (!asset->collec2 || !asset->collec3 || !asset->collec || !asset->exit || 
			!asset->wall || !asset->floor)
		return (ft_free_assets);
	return (asset);
}

void		*ft_free_enemy(t_enemy *enemy, void *mlx)
{
	if (enemy->img_b)
		ft_free_img(enemy->img_b, mlx);
	if (enemy->img_f)
		ft_free_img(enemy->img_f, mlx);
	free(enemy);	
	return (NULL);
}

t_enemy		*ft_init_enemy(void *mlx)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	enemy->img_b = ft_init_img(mlx, "assets/enemy_b.xpm", 0, 0);
	enemy->img_f = ft_init_img(mlx, "assets/enemy_F.xpm", 0, 0);
	if (!enemy->img_b || !enemy->img_f)
		return (ft_free_enemy(enemy, mlx));
	enemy->dir = 0;
	enemy->on_wall = 0;
	return (enemy);
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
		free(line);
		line = get_next_line(o_map->fd_map);
	}
	map = ft_split(str, '\n');
	if (!map)
		return (NULL);
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
	if (map->map == NULL)
		free(map);
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
	data->enemy = ft_init_enemy(data->mlx);
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
	// mlx_string_put(data->mlx, data->win, 0, 25, 0xFFFFFF, str);
	// mlx_string_put(data->mlx, data->win, 0, 25, 0xFF0000 + (data->player->nb_col % data->map->item) * 5, str);
	mlx_string_put(data->mlx, data->win, data->player->x - 35 + data->player->x * SPRITE_SIZE, 
					data->player->y + data->player->y * SPRITE_SIZE - 15, 0x7FF408, str);
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
			if (data->map->map[y][x] == 'S')
				ft_paint(data->enemy->img_f, data->img, x, y);
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
	// ft_printf("%d\n", player->move);
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

void	ft_on_exit(t_data *data)
{
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



int	ft_quit(t_data *data, char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	mlx_loop_end(data->mlx);
	ft_free_mlx(data);
	exit(0);
}

int	ft_notify(t_data *data)
{
	ft_quit(data, NULL);
	return (0);
}

void	ft_check_enemy(t_data *data, int dir)
{
	if (dir == LEFT)
		if (data->map->map[data->player->y][data->player->x - 1] == 'S')
			ft_quit(data, "GAME OVER !");
	if (dir == RIGHT)
		if (data->map->map[data->player->y][data->player->x + 1] == 'S')
			ft_quit(data, "GAME OVER !");
	if (dir == UP)
		if (data->map->map[data->player->y - 1][data->player->x] == 'S')
			ft_quit(data, "GAME OVER !");
	if (dir == DOWN)
		if (data->map->map[data->player->y + 1][data->player->x] == 'S')
			ft_quit(data, "GAME OVER !");
}

void	ft_up(t_data *data)
{
	ft_check_enemy(data, UP);
	if (data->map->map[data->player->y - 1][data->player->x] == 'C')
		data->player->nb_col += 1;
	else if (data->map->map[data->player->y - 1][data->player->x] == 'E')
			ft_on_exit(data);
	if (!(data->map->map[data->player->y - 1][data->player->x] == '1'))
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y - 1][data->player->x] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x, data->player->y - 1);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->y, -1, data->player);
	}
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
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y + 1][data->player->x] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x,  data->player->y + 1);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->y, 1, data->player);
	}
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
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y][data->player->x - 1] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x - 1, data->player->y);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->x, -1, data->player);
	}
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
	{
		if (data->map->map[data->player->y][data->player->x] == 'E')
		{
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
			ft_paint(data->assets->exit, data->img, data->player->x, data->player->y);
		}
		else
		{
			if (data->map->map[data->player->y][data->player->x + 1] == 'C')
				ft_paint(data->assets->floor, data->img, data->player->x + 1, data->player->y);
			data->map->map[data->player->y][data->player->x] = '0';
			ft_paint(data->assets->floor, data->img, data->player->x, data->player->y);
		}
		ft_move(&data->player->x, 1, data->player);
	}
	ft_paint(data->player->img_r, data->img, data->player->x, data->player->y);
	if (data->map->map[data->player->y][data->player->x] != 'E')
		data->map->map[data->player->y][data->player->x] = 'P';
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
}



void	ft_do_move_enemy(t_data *data, int x, int y, int dir)
{
	if (dir == DOWN)
	{
		if (data->map->map[y + 1][x] == 'C' || data->map->map[y + 1][x] == 'S')
		{
			data->enemy->on_wall = 1;
			return ;
		}
		if (data->map->map[y + 1][x] == 'P')
			ft_quit(data, "GAME OVER !");
		data->map->map[y][x] = '0';
		ft_paint(data->assets->floor, data->img, x, y);
		data->map->map[y + 1][x] = 'S';
		ft_paint(data->enemy->img_f, data->img, x, y + 1);
		if (data->map->map[y + 2][x] == '1')
			data->enemy->on_wall = 1;
	}
	else if (dir == UP)
	{
		if (data->map->map[y - 1][x] == 'C')
		{
			data->enemy->on_wall = 0;
			return ;
		}
		if (data->map->map[y - 1][x] == 'P')
			ft_quit(data, "GAME OVER !");
		data->map->map[y][x] = '0';
		ft_paint(data->assets->floor, data->img, x, y);
		data->map->map[y - 1][x] = 'S';
		ft_paint(data->enemy->img_b, data->img, x, y - 1);
		if (data->map->map[y - 2][x] == '1')
			data->enemy->on_wall = 0;
	}
}

void	ft_anim_enemy(t_data *data, int x, int y)
{
	if ((data->map->map[y - 1][x] == 'P' && data->enemy->dir == UP) || (data->map->map[y][x] == 'P' && data->enemy->dir == DOWN))
			ft_quit(data, "GAME OVER !");
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
	mlx_put_image_to_window(data->mlx, data->win, data->img->mlx_img, 0, 0);
	ft_print_steps(data);
	ft_print_collec(data);
	return 0;
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == 'd' || keycode == 65363)
		ft_right(data);
	else if (keycode == 'a' || keycode == 65361)
		ft_left(data);
	else if (keycode == 'w' || keycode == 65362)
		ft_up(data);
	else if (keycode == 's'|| keycode == 65364)
		ft_down(data);
	else if (keycode == 65307)
		ft_quit(data, NULL);
	// int i = 0;
	// while(data->map->map[i])
	// {
	// 	ft_printf("%s\n", data->map->map[i]);
	// 	i++;
	// }
	// ft_printf("\n");
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
	data->c_tick = 0;
	data->e_tick = 0;
	mlx_hook(data->win, 2, (1L << 0), ft_key_hook, data);
	mlx_loop_hook(data->mlx, ft_animations, data);
	mlx_hook(data->win, 17, (1L << 2), ft_notify, data);
	mlx_loop(data->mlx);
}