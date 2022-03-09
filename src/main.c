/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:43:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/09 12:16:43 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		ft_printf("/!\\ Error\nWrong number of arguments !\n");
		exit(1);
	}
	ft_check_extension(av[1]);
	data = ft_init_data(av[1]);
	if (!data)
	{
		ft_printf("/!\\ Error\nInitializing data !\n");
		exit(1);
	}
	ft_render_map(data);
	mlx_hook(data->win, 2, (1L << 0), ft_key_hook, data);
	mlx_hook(data->win, 17, (1L << 0), ft_quit, data);
	mlx_loop(data->mlx);
}
