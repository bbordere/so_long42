/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:44:55 by bbordere          #+#    #+#             */
/*   Updated: 2022/02/24 15:23:34 by bbordere         ###   ########.fr       */
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
	t_img	*exit;
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

typedef struct s_player
{
	t_img	*img_b;
	t_img	*img_f;
	t_img	*img_r;
	t_img	*img_l;
	int		x;
	int		on_exit;
	int		y;
	int		nb_col;
	int		dir;
	int		move;

}	t_player;

typedef	struct s_data
{
	t_assets	*assets;
	t_map		*map;
	t_img		*img;
	t_player	*player;
	int			sprite_size;
	void		*mlx;
	void		*win;
}	t_data;

# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4
# define SPRITE_SIZE 64


int		ft_check_map_char(t_map *map);
void	ft_free_map(char **map);


#endif