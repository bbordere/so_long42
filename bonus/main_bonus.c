/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 10:54:59 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

void	ft_move(int *comp, int set, t_player *player)
{
	*comp += set;
	player->move += 1;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		ft_printf("/!\\ Wrong number of arguments !");
		exit(1);
	}
	ft_check_extension(av[1]);
	data = ft_init_data(av[1]);
	if (!data)
	{
		ft_printf("/!\\Error occured while initializing data !\n");
		exit(1);
	}
	ft_render_map(data);
	data->c_tick = 0;
	data->e_tick = 0;
	mlx_hook(data->win, 2, (1L << 0), ft_key_hook_bonus, data);
	mlx_loop_hook(data->mlx, ft_animations, data);
	mlx_hook(data->win, 17, (1L << 2), ft_notify, data);
	mlx_loop(data->mlx);
}
