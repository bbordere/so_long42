#include "so_long.h"



t_img		*ft_init_img(void *mlx, char *path)
{
	t_img	*img;
	int		size;

	size = 64;
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->mlx_img = mlx_xpm_file_to_image(mlx, path, &size,  &size);
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
	data->win = mlx_new_window(data->mlx, data->map->width * data->sprite_size, 
								data->map->height * data->sprite_size, "so_long");
	return (data);

}

void	ft_destroy_imgs(t_data *data)
{
	mlx_destroy_image(data->mlx, data->assets->floor);
	mlx_destroy_image(data->mlx, data->assets->wall);
	mlx_destroy_image(data->mlx, data->assets->collec);
}

int	ft_esc(t_data *data)
{
	
	ft_destroy_imgs(data);		
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	return (0);
}

unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	unsigned int	color;
	char			*pix;

	pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pix;
	return (color);
}


void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_data 	*data;
	int		x;
	int		y;
	
	data = ft_init_data("map/map.ber");
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		data->map->x = 0;
		while (x < data->map->width)
		{
			if (data->map->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->assets->wall->mlx_img, data->map->x, data->map->y);
			else
				mlx_put_image_to_window(data->mlx, data->win, data->assets->floor->mlx_img, data->map->x, data->map->y);
			data->map->x += data->sprite_size;
			x++;
		}
		data->map->y += data->sprite_size;
		y++;
	}
	mlx_hook(data->win, 2,1L<<0, ft_esc, &data);
	mlx_loop(data->mlx);
}