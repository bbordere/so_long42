/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:44:55 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/18 15:08:48 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
// # include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"


typedef	struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_assets
{
    t_img	*floor;
    t_img	*wall;
    t_img	*collec;
	t_img	*tmp;
}	t_assets;

typedef struct s_map
{
	int		x;
	int		y;
	int		width;
	int		item;
	int		exit;
	int		start;
	int		height;
	char	**map;
	int		fd_map;
}	t_map;

typedef	struct s_data
{
	t_assets	*assets;
	t_map		*map;
	int			sprite_size;
	void		*mlx;
	void		*win;
}	t_data;

int	ft_check_map_char(t_map *map);


#endif