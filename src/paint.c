/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:20:35 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/06 23:20:35 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned int	ft_get_pixel(t_img *img, int x, int y)
{
	unsigned int	color;
	char			*pix;

	pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pix;
	return (color);
}

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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
				ft_put_pixel(mlx_img, (x * SPRITE_SIZE) + x1,
					(y * SPRITE_SIZE) + y1, color);
		}
	}	
}
