/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:54:26 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 09:54:26 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_print_steps(t_data *data)
{
	char	*str;

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
	mlx_string_put(data->mlx, data->win,
		data->player->x - 35 + data->player->x * SPRITE_SIZE,
		data->player->y + data->player->y * SPRITE_SIZE - 15, 0x7FF408, str);
	free(str);
	free(item);
}
