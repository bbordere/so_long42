/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/06 23:35:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

// void	ft_print_steps(t_data *data)
// {
// 	char *str;

// 	str = ft_strjoin(ft_itoa(data->player->move), " steps");
// 	mlx_string_put(data->mlx, data->win, 0, 10, 0xFFFFFF, str);
// 	free(str);
// }

// void	ft_print_collec(t_data *data)
// {
// 	char	*str;
// 	char	*col;
// 	char	*item;

// 	col = ft_itoa(data->player->nb_col);
// 	item = ft_itoa(data->map->item);
// 	str = ft_strjoin(col, " / ");
// 	str = ft_strjoin(str, item);
// 	str = ft_strjoin(str, " collectibles");
// 	mlx_string_put(data->mlx, data->win, 0, 25, 0xFFFFFF, str);
// 	// mlx_string_put(data->mlx, data->win, 0, 25, 0xFF0000 + (data->player->nb_col % data->map->item) * 5, str);
// 	// mlx_string_put(data->mlx, data->win, data->player->x - 35 + data->player->x * SPRITE_SIZE, 
// 	// 				data->player->y + data->player->y * SPRITE_SIZE - 15, 0x7FF408, str);
// 	free(str);
// 	free(item);
// }

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
	// ft_print_steps(data);
	// ft_print_collec(data);
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
	// ft_print_steps(data);
	// ft_print_collec(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data 	*data;
	
	(void)ac;
	data = ft_init_data(av[1]);
	ft_printf("%d\n", data->map->item);
	ft_render_map(data);
	mlx_hook(data->win, 2, (1L << 0), ft_key_hook, data);
	mlx_hook(data->win, 17, (1L << 0), ft_quit, data);
	// mlx_loop_hook(data->mlx, ft_key_hook, data);
	mlx_loop(data->mlx);

}