/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:01:03 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 10:01:03 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	ft_quit_msg(t_data *data, char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	mlx_loop_end(data->mlx);
	ft_free_mlx(data);
	exit(0);
}

int	ft_notify(t_data *data)
{
	ft_quit_msg(data, NULL);
	return (0);
}

int	ft_key_hook_bonus(int keycode, t_data *data)
{
	ft_key_hook(keycode, data);
	ft_print_steps(data);
	ft_print_collec(data);
	return (0);
}
