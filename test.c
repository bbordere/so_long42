#include "so_long.h"


t_assets    *ft_init_assets(void *mlx)
{
	t_assets    *asset;
	int 		size;

	asset = malloc(sizeof(t_assets *));
	if (!asset)
		return (NULL);
	size = 64;
	asset -> wall = mlx_xpm_file_to_image(mlx, "assets/wall.xpm", &size,  &size);
	asset -> floor = mlx_xpm_file_to_image(mlx, "assets/clay.xpm", &size, &size);
	asset -> collec = mlx_xpm_file_to_image(mlx, "assets/amethyst.xpm", &size, &size);
	return (asset);
}

void    ft_len_map(int *W, int *H)
{
	int     fd;
	char    *line;

	fd = open("map/map.ber", O_RDONLY);
	line = get_next_line(fd);
	*W = ft_strlen(line) - 1;
	*H = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			close(fd);
			break ;
		}
		*H += 1;
		free(line);
	}
}

t_game	*ft_init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game *));
	if (!game)
		return (NULL);
	game->height = 0;
	game->width = 0;
	game->sprite_size = 64;
	game->mlx = mlx_init();
	ft_len_map(&(game->width), &(game->height));
	game->win = mlx_new_window(game->mlx, game->width * game->sprite_size, 
								game->height * game->sprite_size, "so_long");
	return (game);

}

t_map	*ft_init_map(char *file)
{
	t_map	*map;

	map = malloc(sizeof(t_map *));
	if (!map)
		return (NULL);
	map->fd_map = open(file, O_RDONLY);
	if (map->fd_map == -1)
		return (NULL);
	map->x = 0;
	map->y = 0;
	return (map);
}

int	ft_esc(t_game *game)
{
		mlx_destroy_window(game->mlx, game->win);
		// game->win = NULL;
	// if (key == 27)
	// {
	// 
	// }
	return (0);
}

int	main(void)
{
	t_game 		*game;
	t_assets 	*assets;
	t_map		*map;
	char    *line;
	int		i;
	
	game = ft_init_game();
	assets = ft_init_assets(game->mlx);
	map = ft_init_map("map/map.ber");

	while (1)
	{
		map->x = 0;
		i = 0;
		line = get_next_line(map->fd_map);
		if (!line)
			break ;
		while (line[i] && line[i]!= '\n')
		{
			if (line[i] == '1')
				mlx_put_image_to_window(game->mlx, game->win, assets -> wall, map->x, map->y);
			else
				mlx_put_image_to_window(game->mlx, game->win, assets -> floor, map->x, map->y);
			// if (line[i] == 'C')
			// 	mlx_put_image_to_window(game->mlx, game->win, assets -> collec, map->x, map->y);
			map->x += game->sprite_size;
			i++;
		}
		map->y += game->sprite_size;
		free(line);
	}
	
	// mlx_loop_hook(game->mlx, &ft_esc, &game);
	mlx_hook(game->win, 2,1L<<0, ft_esc, &game);
	mlx_loop(game->mlx);
	// mlx_destroy_display(game->mlx);
}