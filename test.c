#include "so_long.h"


t_assets    *ft_init_assets(void *mlx)
{
    t_assets    *asset;

    asset = malloc(sizeof(t_assets));
    if (!asset)
        return (NULL);
    int size = 64;
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
    *W = ft_strlen(line);
    *H += 1;
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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
    int     WIDTH;
    int     HEIGHT;
    int     LEN_IMG = 64;
    void    *img;
    char    *line;
    int     fd = open("map/map.ber", O_RDONLY);

	mlx = mlx_init();
    WIDTH = 0;
    HEIGHT = 0;

    ft_len_map(&WIDTH, &HEIGHT);
	mlx_win = mlx_new_window(mlx, WIDTH * LEN_IMG, HEIGHT * LEN_IMG, "so_long");

    int     i;
    int     y = 0;
    int     x = 0;
    t_assets *assets;
    assets = ft_init_assets(mlx);

    while (1)
    {
        x = 0;
        i = 0;
        line = get_next_line(fd);        
        if (!line)
            break ;
        while (line[i])
        {
            if (line[i] == '1')
                mlx_put_image_to_window(mlx, mlx_win, assets -> wall, x, y);
            else
                mlx_put_image_to_window(mlx, mlx_win, assets -> floor, x, y);
            // if (line[i] == 'C')
            //     mlx_put_image_to_window(mlx, mlx_win, assets -> collec, x, y);
            x += LEN_IMG;
            i++;
        }
        y += LEN_IMG;
        free(line);
    }
    mlx_loop(mlx);
}