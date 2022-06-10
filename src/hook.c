/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 08:52:50 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 08:52:50 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_quit(t_data *data)
{
	mlx_loop_end(data->mlx);
	close(data->map->fd_map);
	ft_free_mlx(data);
	exit(0);
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == 'd' || keycode == 65363)
		ft_right(data);
	else if (keycode == 'a' || keycode == 65361)
		ft_left(data);
	else if (keycode == 'w' || keycode == 65362)
		ft_up(data);
	else if (keycode == 's' || keycode == 65364)
		ft_down(data);
	else if (keycode == 65307)
		ft_quit(data);
	return (0);
}

void	*ft_free_map_data(t_data *data)
{
	ft_free_map(data->map->map);
	free(data->map);
	return (ft_free(data));
}
